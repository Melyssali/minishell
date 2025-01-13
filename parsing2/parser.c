/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2025/01/04 19:32:49 by melyssa          ###   ########.fr       */
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
	data->ptr_head_redir = NULL;
	data->ptr_current_redir = NULL;
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
	t_redirection *temp;

	temp = NULL;
	// On pointe vers le premier noeud redirection
	if (!data->ptr_head_redir)
	{
		data->ptr_head_redir = (*new_node)->redirection;
		data->ptr_current_redir = data->ptr_head_redir;
	}
	// on crée plusieurs noeuds redirection dans le noeud principal (sans pipe)
	else if (data->ptr_head_redir == (*new_node)->redirection)
	{
		temp = create_node_redir();
		data->ptr_current_redir->next = temp;
		data->ptr_current_redir = temp;
	}
	// avec pipe / nouveau noeud redirection dans un nouveau noeud principal
	else
		data->ptr_current_redir = (*new_node)->redirection;
	if (data->operator_type == REDIR_OUTPUT
		|| data->operator_type == APPEND_OUTPUT)
	{
		data->ptr_current_redir->append_output = (data->operator_type == APPEND_OUTPUT);
		data->ptr_current_redir->output_file = ft_strdup(data->tokens[++(*i)]);
	}
	else if (data->operator_type == REDIR_INPUT)
	{
		data->ptr_current_redir->input_file = ft_strdup(data->tokens[++(*i)]);
	}
	else if (data->operator_type == HEREDOC)
	{
		data->ptr_current_redir->heredoc_delimiter = ft_strdup(data->tokens[++(*i)]);
		handle_heredoc(data->ptr_head_redir->heredoc_delimiter, *new_node);
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
	data->ptr_head_redir = NULL;
	(*current) = *new_node;
	data->pipe_count++;
	(*i)--;
}
