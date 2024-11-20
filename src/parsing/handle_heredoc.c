/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/19 21:40:45 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <readline/readline.h>


void	handle_heredoc(char *delimiter, t_command_line *node)
{
	char *input;
	int i;

	i = 0;
	input = readline("> ");
	while (ft_strcmp(input, delimiter) != 0)
	{
		fill_lines(input, node, i);
		input = readline("> ");
		rl_on_new_line();
		rl_replace_line(input, 0);
		i++;
	}
}

void	fill_lines(char *input, t_command_line *node, int index)
{
	char **temp_arr;
	static int capacity;
	int i;

	i = 0;
	if (index == 0)
	{
		capacity = INITIAL_SIZE;
		node->lines_heredoc = malloc(sizeof(char *) * (capacity + 1));
	}
	if (index < capacity)
	{
		node->lines_heredoc[index] = ft_strdup(input);
		node->lines_heredoc[index + 1] = NULL;
	}
	else
	{
		capacity *= 2;
		temp_arr = malloc(sizeof(char *) * (capacity + 1));
		while (node->lines_heredoc[i])
		{
			temp_arr[i] = ft_strdup(node->lines_heredoc[i]);
			i++;
		}
		temp_arr[i] = ft_strdup(input);
		temp_arr[i + 1] = NULL;
		free(node->lines_heredoc);
		node->lines_heredoc = temp_arr;
	}
}
