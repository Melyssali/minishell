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

// when you pass -1 in first argument to waitpid, it waits for any child process
// to terminate without needing to build a PID list.
// errno is defined to ECHILD if there are no child processes to wait for, so it 
// break this loop while (wait_pid != -1 || errno != ECHILD) to avoid infinite loop.

// WIFSIGNALED returns true if the child process was terminated by a signal.
// WTERMSIG returns the number of the signal that caused the child process to terminate.
// WEXITSTATUS returns the exit status of the child process.

int wait_for_all(pid_t pid)
{
    pid_t wait_pid;
    int status;
    int last_status;

    wait_pid = 0;
	last_status = 0;
    while (wait_pid != -1 || errno != ECHILD)
        {
            wait_pid = waitpid(-1, &status, 0);
            if (wait_pid == pid)
                last_status = status;
        }
    if (WIFSIGNALED(last_status) && WTERMSIG(last_status) == SIGPIPE)
		return (0);
	else if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	else if (WIFEXITED(last_status) && !WIFSIGNALED(last_status))
		return (WEXITSTATUS(last_status));
	return (last_status);
}


