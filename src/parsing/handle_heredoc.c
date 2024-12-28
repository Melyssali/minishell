/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/27 21:17:26 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	write_heredoc(char *delimiter, int fd)
{
	char	*input;

	input = NULL;
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
}

void	handle_heredoc(char *delimiter, t_command_line *node)
{
	int		fd;
	char	*file_path;

	file_path = "/tmp/heredoc_tmp";
	fd = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
	{
		perror("Error:");
		return ;
	}
	write_heredoc(delimiter, fd);
	close(fd);
	node->redirection->heredoc_file = ft_strdup(file_path);
	if (!node->redirection->heredoc_file)
		perror("Error:");
}
