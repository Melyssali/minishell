/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/28 21:34:14 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

int	calculate_width(char **tokens, int *index)
{
	while (tokens[*index] && ft_strcmp(tokens[*index], REDIR_INPUT) != 0 && ft_strcmp(tokens[*index], REDIR_OUTPUT) != 0 &&
			ft_strcmp(tokens[*index], PIPE) != 0 && ft_strcmp(tokens[*index], APPEND_OUTPUT) != 0 && ft_strcmp(tokens[*index], HEREDOC) != 0)
		(*index)++;
	return (*index);
}
char	**duplicate_arr(char **tokens, int *index)
{
	char **arr;
	int width;
	int	y;
	int i;

	y = 0;
	i = *index;
	width = calculate_width(tokens, index) - i;
	arr = malloc(sizeof(char *) * width + 1);
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
t_command_line	*create_node(char **tokens, int *index, t_builtin *hash_table[])
{
	t_command_line	*node;

	node = malloc(sizeof(t_command_line));
	if (!node)
	{
		printf("Malloc failed.");
		exit(EXIT_FAILURE);
	}
	node->command = duplicate_arr(tokens, index);
	node->is_builtin = is_builtin_command(node->command[0], hash_table);
	node->input_file = NULL;
	node->output_file = NULL;
	node->append_output = 0;
	node->heredoc_delimiter = NULL;
	node->next = NULL;
	return (node);
}
