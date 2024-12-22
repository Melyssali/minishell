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

int wait_for_all(t_minishell *minishell, int pid_nbr)
{
    int index;
    int status;
    int last_status = 0;
    pid_t wait_pid;

    index = pid_nbr - 1;
    while (index >= 0)
    {
        wait_pid = waitpid(minishell->data->pid_table[index], &status, 0);
        if (wait_pid == minishell->data->pid)
            last_status = status;
        index--;
    }
    if (WIFSIGNALED(last_status))
    {
        if (WTERMSIG(last_status) == SIGPIPE)
            return (0);
        return (128 + WTERMSIG(last_status));
    }
    if (WIFEXITED(last_status))
        return (WEXITSTATUS(last_status));
    return (last_status);
}
