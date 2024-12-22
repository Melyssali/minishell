/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/18 17:17:50 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execution(t_minishell *minishell)
{
	int pid_nbr;

	pid_nbr = 0;
	minishell->data->pid_table = malloc(sizeof(pid_t) * minishell->data->pipe_count + 1);
	save_or_restore_fds(minishell, SAVE);
	while (minishell->command_line != NULL)
	{
		exec_loop(minishell, pid_nbr);
		skip_and_free(minishell);
		save_or_restore_fds(minishell, RESTORE);
		pid_nbr++;
	}
	minishell->data->return_value = wait_for_all(minishell, pid_nbr);
	free(minishell->data->pid_table);
	minishell->data->pid_table = NULL;
	return (SUCCESS);
}

int	exec_loop(t_minishell *minishell, int pid_nbr)
{
	int	fd_tab[2];

	if (pipe(fd_tab) == -1)
	{
		perror("pipe");
		return (FAIL);
	}
	if (setup_redirections(minishell->command_line, fd_tab) == FAIL)
		return (FAIL);
	if (minishell->command_line->is_builtin == TRUE)
			return (execute_builtin(minishell));
	else
		if (exec_cmd(minishell, pid_nbr) == FAIL)
			return (FAIL);
	return (SUCCESS);
}

int	exec_cmd(t_minishell *minishell, int pid_nbr)
{
	if (build_cmd(minishell) == FAIL)
		return (FAIL);
	minishell->data->pid_table[pid_nbr] = fork();
	if (minishell->data->pid_table[pid_nbr] == -1)
	{
		perror("fork");
		return (FAIL);
	}
	if (minishell->data->pid_table[pid_nbr] == 0)
		child_process(minishell);
	return (SUCCESS);
}

void	child_process(t_minishell *minishell)
{
	char	**envp;

	envp = lst_to_arr(minishell->env);
	if (!envp)
		return ; // need to free
	if (execve(minishell->command_line->cmd_path,
			minishell->command_line->command, envp) == -1)
		perror("execve");
}

