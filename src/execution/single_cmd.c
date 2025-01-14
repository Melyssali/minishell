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

/*--------------------Prototypes----------------------*/
static void single_builtin(t_minishell *minishell);
static void single_extern_cmd(t_minishell *minishell);
/*----------------------------------------------------*/

void single_cmd(t_minishell *minishell)
{
    if (minishell->command_line->is_builtin == TRUE)
		single_builtin(minishell);
    else
        single_extern_cmd(minishell);
}

static void single_builtin(t_minishell *minishell)
{
	if (file_redir(minishell->command_line) == FAIL)
	{
		minishell->data->return_value = FAIL;
		return ;
	}
	execute_builtin(minishell);
}

static void single_extern_cmd(t_minishell *minishell)
{
	pid_t single_pid;

	single_pid = fork();
	if (single_pid == -1)
	{
		perror("fork");
		return ;
	}
	if (single_pid == 0)
		extern_cmd_child(minishell);
	else
		waitpid(single_pid, NULL, 0);
}