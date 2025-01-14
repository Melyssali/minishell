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

/*---------------------Prototypes----------------------*/
static int	handle_infile(t_redirection *redirection);
static int	handle_outfile(t_redirection *redirection);
/*-----------------------------------------------------*/

int	file_redir(t_command_line *command_line)
{
	t_command_line	*tmp;

	tmp = command_line;
	while (tmp != NULL)
	{
		if (tmp->redirection->input_file != NULL)
		{
			if (handle_infile(tmp->redirection) == FAIL)
				return (FAIL);
		}
		if (tmp->redirection->output_file != NULL)
		{
			if (handle_outfile(tmp->redirection) == FAIL)
				return (FAIL);
		}
		if (tmp->redirection->next != NULL)
			tmp->redirection = tmp->redirection->next;
		else if (tmp->redirection->next == NULL)
			return (SUCCESS);
	}
	return (SUCCESS);
}

static int	handle_infile(t_redirection *redirection)
{
	if (access(redirection->input_file, F_OK) != 0)
	{
		print_error(" No such file or directory\n");
		return (FAIL);
	}
	if (access(redirection->input_file, R_OK) != 0)
	{
		printf("error while reading file\n");
		return (FAIL);
	}
	redirection->file_in = open(redirection->input_file, O_RDONLY);
	if (redirection->file_in == -1)
	{
		printf("error while opening file\n");
		return (FAIL);
	}
	dup2(redirection->file_in, STDIN_FILENO);
	close(redirection->file_in);
	return (SUCCESS);
}

static int	handle_outfile(t_redirection *redirection)
{
	if (redirection->append_output > 0)
		redirection->file_out = open(redirection->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		redirection->file_out = open(redirection->output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redirection->file_out == -1)
	{
		if (errno == EACCES)
		{
			print_error("minishell: ");
			print_error(redirection->output_file);
			print_error(": Permission denied\n");
		}
		else
			perror("minishell: open failed");
		return (FAIL);
	}
	dup2(redirection->file_out, STDOUT_FILENO);
	close(redirection->file_out);
	return (SUCCESS);
}

void	pipe_redir(t_minishell *minishell)
{
	if (minishell->command_line->prev
		&& minishell->command_line->redirection->input_file == NULL)
	{
		dup2(minishell->command_line->prev->redirection->pipe[0], STDIN_FILENO);
	}
	if (minishell->command_line->next
		&& minishell->command_line->redirection->output_file == NULL)
	{
		dup2(minishell->command_line->redirection->pipe[1], STDOUT_FILENO);
	}
	if (minishell->command_line->prev)
	{
		close(minishell->command_line->prev->redirection->pipe[0]);
		close(minishell->command_line->prev->redirection->pipe[1]);
	}
	if (minishell->command_line->next)
	{
		close(minishell->command_line->redirection->pipe[0]);
		close(minishell->command_line->redirection->pipe[1]);
	}
}
