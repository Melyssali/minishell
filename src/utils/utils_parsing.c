/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/29 14:07:09 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

int	calculate_width(t_hash_operators *table_operators[], char *tokens[],
		int *index)
{
	int	operator_type;

	while (tokens[*index])
	{
		operator_type = get_operator_type(table_operators, tokens[*index]);
		if (operator_type != REDIR_INPUT && operator_type != REDIR_OUTPUT
			&& operator_type != PIPE && operator_type != APPEND_OUTPUT
			&& operator_type != HEREDOC)
			(*index)++;
		else
			break;
	}
	return (*index);
}
char	**duplicate_arr(t_hash_operators *table_operators[], char *tokens[],
		int *index)
{
	char	**arr;
	int		width;
	int		y;
	int		i;

	y = 0;
	i = *index;
	width = calculate_width(table_operators, tokens, index) - i;
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
t_command_line	*create_node(t_hash_operators *table_operators[],
		char *tokens[], int *index, t_hash_builtins *table_builtins[])
{
	t_command_line	*node;

	node = malloc(sizeof(t_command_line));
	if (!node)
	{
		printf("Malloc failed.");
		exit(EXIT_FAILURE);
	}
	node->command = duplicate_arr(table_operators, tokens, index);
	node->is_builtin = is_builtin_command(node->command[0], table_builtins);
	node->input_file = NULL;
	node->output_file = NULL;
	node->append_output = 0;
	node->heredoc_delimiter = NULL;
	node->next = NULL;
	return (node);
}
