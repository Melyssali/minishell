/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/24 14:40:36 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void setup_redirections(t_command_line *command_line, int *pipe)
{
	close(pipe[0]);
	if (command_line->input_file != NULL)
		redirect_input(command_line);
	if (command_line->output_file != NULL)
		redirect_output(command_line);
	else if (command_line->next != NULL)
		dup2(pipe[1], STDOUT_FILENO);
	close(pipe[1]);
}

int redirect_input(t_command_line *command_line)
{
	int fd_in;
	
	fd_in = open(command_line->input_file, O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error opening input file");
		return (FAIL);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);

	return SUCCESS;
}

int redirect_output(t_command_line *command_line)
{
	int fd_out;
	
	 if (command_line->append_output > 0)
        {
            fd_out = open(command_line->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
    else
        {
            fd_out = open(command_line->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
    if (fd_out == -1)
        {
            perror("Error opening output file");
            return FAIL;
        }
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return SUCCESS;
}
