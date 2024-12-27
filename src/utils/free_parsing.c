/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/26 20:25:27 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_operators_table(t_hash_operators *table_op[])
{
	int					i;
	t_hash_operators	*current;
	t_hash_operators	*next;

	i = -1;
	while (++i < TABLE_OP_SIZE)
	{
		current = table_op[i];
		while (current)
		{
			next = current->next;
			free(current->key);
			free(current);
			current = next;
		}
		table_op[i] = NULL;
	}
}

void	free_builtins_table(t_hash_builtins *table_builtins[])
{
	int				i;
	t_hash_builtins	*current;
	t_hash_builtins	*next;

	i = -1;
	while (++i < TABLE_BUILTINS_SIZE)
	{
		current = table_builtins[i];
		while (current)
		{
			next = current->next;
			free(current->key);
			free(current);
			current = next;
		}
		table_builtins[i] = NULL;
	}
}

void	free_nodes_parsing(t_command_line *head)
{
	t_command_line	*current;
	t_command_line	*next;

	current = head;
	while (current)
	{
		next = current->next;
		if (current->command)
			free_arr_tokenization(current->command);
		if (current->cmd_path)
			free(current->cmd_path);
		if (current->input_file)
			free_arr_tokenization(current->input_file);
		if (current->output_file)
			free_arr_tokenization(current->output_file);
		if (current->heredoc_delimiter)
			free(current->heredoc_delimiter);
		if (current->heredoc_file)
			free(current->heredoc_file);
		free(current);
		current = next;
	}
}

void	free_arr_tokenization(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_all_parsing(t_command_line *head, t_hash_operators *table_op[],
		t_hash_builtins *table_builtins[])
{
	free_builtins_table(table_builtins);
	free_operators_table(table_op);
	free_nodes_parsing(head);
}
