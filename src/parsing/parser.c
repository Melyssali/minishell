/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/26 21:26:29 by melyssa          ###   ########.fr       */
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
	data->output_i = -1;
	data->input_i = -1;
	data->pipe_count = 0;
	i = 0;
	new_node = create_node(data, &i);
	if (!head)
		head = new_node;
	current = new_node;
	handle_operators(&i, &new_node, data, &current);
	return (head);
}

void	handle_redirections(t_command_line **new_node, t_data *data, int *i)
{
	if (data->operator_type == REDIR_OUTPUT
		|| data->operator_type == APPEND_OUTPUT)
	{
		data->output_i++;
		(*new_node)->append_output = (data->operator_type == APPEND_OUTPUT);
		if ((*new_node)->output_file == NULL)
			(*new_node)->output_file = malloc_array(data, &data->tokens[(*i)], data->tokens[(*i)][0]);
		(*new_node)->output_file[data->output_i] = ft_strdup(data->tokens[++(*i)]);
		printf("output array index : %d : %s\n", data->output_i, (*new_node)->output_file[data->output_i]);
	}
	else if (data->operator_type == REDIR_INPUT)
	{
		data->input_i++;
		if ((*new_node)->input_file == NULL)
			(*new_node)->input_file = malloc_array(data, &data->tokens[(*i)], data->tokens[(*i)][0]);
		(*new_node)->input_file[data->input_i] = ft_strdup(data->tokens[++(*i)]);
		printf("input array index : %d : %s\n", data->input_i, (*new_node)->input_file[data->input_i]);
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
	*new_node = create_node(data, i);
	(*current)->next = *new_node;
	(*current) = *new_node;
	data->pipe_count++;
	(*i)--;
}
