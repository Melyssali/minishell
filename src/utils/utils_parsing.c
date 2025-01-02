/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2025/01/02 14:23:39 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	calculate_width(t_hash_operators *table_op[], char *tokens[], int *index)
{
	int	operator_type;

	while (tokens[*index])
	{
		operator_type = get_operator_type(table_op, tokens[*index]);
		if (operator_type == -1)
			(*index)++;
		else
			break ;
	}
	return (*index);
}

char	**duplicate_arr(t_hash_operators *table_op[], char *tokens[],
		int *index)
{
	char	**arr;
	int		width;
	int		y;
	int		i;

	y = 0;
	i = *index;
	width = calculate_width(table_op, tokens, index) - i;
	if (*index == 0)
		return (NULL);
	arr = malloc(sizeof(char *) * (width + 1));
	if (!arr)
		return (NULL);
	arr[width] = NULL;
	while (y < width)
	{
		arr[y] = ft_strdup(tokens[i]);
		y++;
		i++;
	}
	arr[y] = NULL;
	return (arr);
}

t_command_line	*create_node(t_hash_operators *table_op[], char *tokens[],
		int *index, t_hash_builtins *table_builtins[])
{
	t_command_line	*node;

	node = malloc(sizeof(t_command_line));
	if (!node)
		exit(EXIT_FAILURE);
	node->command = duplicate_arr(table_op, tokens, index);
	if (node->command == NULL)
	{
		node->builtin_type = 0;
		node->is_builtin = 0;
	}
	else
	{
		node->builtin_type = is_builtin_command(node->command[0],
				table_builtins);
		node->is_builtin = (node->builtin_type != -1);
	}
	node->redirection = NULL;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

t_redirection	*create_node_redir(void)
{
	t_redirection	*node_redir;

	node_redir = malloc(sizeof(t_redirection));
	if (!node_redir)
		exit(EXIT_FAILURE);
	node_redir->append_output = 0;
	node_redir->input_file = NULL;
	node_redir->output_file = NULL;
	node_redir->heredoc_delimiter = NULL;
	node_redir->heredoc_file = NULL;
	node_redir->next = NULL;
	return (node_redir);
}