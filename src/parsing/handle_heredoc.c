/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/20 12:54:47 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_heredoc(char *delimiter, t_command_line *node)
{
	int	fd;
	char *file_path;
	char *input;

	input = NULL;
	file_path = "/tmp/heredoc_tmp";
	fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
 		perror("Error:");
		return ;
	}
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	close(fd);
	node->heredoc_file = ft_strdup(file_path);
	if (!node->heredoc_file)
		perror("Error:");
}
