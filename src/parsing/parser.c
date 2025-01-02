/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/27 23:04:01 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This file processes the input and creates a linked list to pass
// to the execution part
int	is_builtin_command(char *cmd, t_hash_builtins *table_builtins[])
{
	return (search(table_builtins, cmd));
}

static void	handle_operators(int *i, t_command_line **new_node, t_data *data,
							t_command_line **current)
{
	while (data->tokens[*i])
	{
		data->operator_type = get_operator_type(data->table_op,
				data->tokens[*i]);
		if (data->operator_type >= REDIR_OUTPUT
			&& data->operator_type <= HEREDOC)
			handle_redirections(new_node, data, i);
		else if (data->operator_type == PIPE)
			handle_pipe(current, new_node, data, i);
		(*i)++;
	}
}

t_command_line	*parsing(t_data *data)
{
	t_command_line	*head;
	t_command_line	*current;
	t_command_line	*new_node;
	int				i;

	head = NULL;
	current = NULL;
	new_node = NULL;
	data->node_redir = NULL;
	data->current_redir = NULL;
	data->pipe_count = 0;
	i = 0;
	new_node = create_node(data->table_op, data->tokens, &i,
			data->table_builtins);
	if (!head)
		head = new_node;
	current = new_node;
	handle_operators(&i, &new_node, data, &current);
	return (head);
}

void	handle_redirections(t_command_line **new_node, t_data *data, int *i)
{
	data->node_redir = create_node_redir();
	if (!(*new_node)->redirection)
		(*new_node)->redirection = data->node_redir;
	if (data->current_redir)
		data->current_redir->next = data->node_redir;
	data->current_redir = data->node_redir;
	if (data->operator_type == REDIR_OUTPUT
		|| data->operator_type == APPEND_OUTPUT)
	{
		data->node_redir->append_output = (data->operator_type == APPEND_OUTPUT);
		data->node_redir->output_file = ft_strdup(data->tokens[++(*i)]);
	}
	else if (data->operator_type == REDIR_INPUT)
	{
		data->node_redir->input_file = ft_strdup(data->tokens[++(*i)]);
	}
	else if (data->operator_type == HEREDOC)
	{
		data->node_redir->heredoc_delimiter = ft_strdup(data->tokens[++(*i)]);
		handle_heredoc(data->node_redir->heredoc_delimiter, *new_node);
	}
}

void	handle_pipe(t_command_line **new_node, t_command_line **current,
		t_data *data, int *i)
{
	(*i)++;
	*new_node = create_node(data->table_op, data->tokens, i,
			data->table_builtins);
	(*new_node)->prev = *current;
	(*current)->next = *new_node;
	(*current) = *new_node;
	data->pipe_count++;
	(*i)--;
}