/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/07 17:25:55 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This file processes the input and creates a linked list to pass
// to the execution part
int	is_builtin_command(char *cmd, t_hash_builtins *table_builtins[])
{
	return (search(table_builtins, cmd));
}
// gestion erreur : ls > touch "file.txt"
// ne fonctionne pas car une redirection peut pas se faire
// sur un executable

// GERER   < ls | wc -l
//  ls > test ok -- output ecrit que "test" et pas test ok

t_command_line	*parsing(t_data *data)
{
	t_command_line	*head;
	t_command_line	*current;
	t_command_line	*new_node;
	int				i;

	head = NULL;
	current = NULL;
	new_node = NULL;
	data->pipe_count = 0;
	i = 0;
	new_node = create_node(data->table_op, data->tokens, &i,
			data->table_builtins);
	if (!head)
		head = new_node;
	current = new_node;
	while (data->tokens[i])
	{
		data->operator_type = get_operator_type(data->table_op,
				data->tokens[i]);
		if (data->operator_type >= REDIR_OUTPUT
			&& data->operator_type <= HEREDOC)
			handle_redirections(&new_node, data, &i);
		else if (data->operator_type == PIPE)
			handle_pipe(&current, &new_node, data, &i);
		i++;
	}
	return (head);
}

void	handle_redirections(t_command_line **new_node, t_data *data, int *i)
{
	if (data->operator_type == REDIR_OUTPUT
		|| data->operator_type == APPEND_OUTPUT)
	{
		(*new_node)->append_output = (data->operator_type == APPEND_OUTPUT);
		(*new_node)->output_file = ft_strdup(data->tokens[++(*i)]);
	}
	else if (data->operator_type == REDIR_INPUT)
	{
		(*new_node)->input_file = ft_strdup(data->tokens[++(*i)]);
	}
	else if (data->operator_type == HEREDOC)
	{
		(*new_node)->heredoc_delimiter = ft_strdup(data->tokens[++(*i)]);
		handle_heredoc((*new_node)->heredoc_delimiter, *new_node);
	}
}

void	handle_pipe(t_command_line **new_node, t_command_line **current,
		t_data *data, int *i)
{
	(*i)++;
	*new_node = create_node(data->table_op, data->tokens, i,
			data->table_builtins);
	(*current)->next = *new_node;
	(*current) = *new_node;
	data->pipe_count++;
	(*i)--;
}
