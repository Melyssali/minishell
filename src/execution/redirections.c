/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/27 21:18:12 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	setup_redirections(t_command_line *command_line, int *pipe)
{
	int	return_value;

	return_value = SUCCESS;
	close(pipe[0]);
	if (command_line->redirection->input_file != NULL)
	{
		if (handle_infile(command_line) == FAIL)
			return_value = FAIL;
	}
	if (command_line->redirection->output_file != NULL)
	{
		if (handle_outfile(command_line) == FAIL)
			return_value = FAIL;
	}
	else if (command_line->next != NULL)
		dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
	return (return_value);
}

int	handle_infile(t_command_line *command_line)
{
	int	return_value;
	int	fd_in;

	return_value = SUCCESS;
	if (access(command_line->redirection->input_file, F_OK) != 0)
	{
		print_error(" No such file or directory\n");
		return (FAIL);
	}
	if (access(command_line->redirection->input_file, R_OK) != 0)
	{
		printf("error while reading file\n");
		return (FAIL);
	}
	fd_in = open(command_line->redirection->input_file, O_RDONLY);
	if (fd_in == -1)
	{
		printf("error while opening file\n");
		return_value = FAIL;
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (return_value);
}

int	handle_outfile(t_command_line *command_line)
{
	int	fd_out;

	if (command_line->redirection->append_output > 0)
		fd_out = open(command_line->redirection->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(command_line->redirection->output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		if (errno == EACCES)
		{
			print_error("minishell:");
			print_error(command_line->redirection->output_file);
			print_error(": Permission denied\n");
		}
		else
			perror("minishell: open failed");
		return (FAIL);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (SUCCESS);
}

void	save_or_restore_fds(t_minishell *minishell, int order)
{
	if (order == SAVE)
	{
		minishell->data->save_stdin = dup(STDIN_FILENO);
		minishell->data->save_stdout = dup(STDOUT_FILENO);
	}
	else if (order == RESTORE)
	{
		dup2(minishell->data->save_stdin, STDIN_FILENO);
		dup2(minishell->data->save_stdout, STDOUT_FILENO);
	}
}
