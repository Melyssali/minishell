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

/*-----------------Prototypes------------------*/
static void close_fds(t_minishell *minishell);
static int wait_for_all(t_minishell *minishell);
// static void free_execution(t_minishell *minishell);
/*---------------------------------------------*/

void execution(t_minishell *minishell)
{
	t_command_line *tmp;
	int count;

	count = 0;
	minishell->command_line = minishell->command_line_head;
	tmp = minishell->command_line;
	while(tmp != NULL)
	{
		count++;
		tmp = tmp->next;
	}
	minishell->data->pipe_count = count - 1;
	if (!minishell->command_line->next)
	{
		single_cmd(minishell);
	}
	else
	{
		pipeline_cmd(minishell, count);
		close_fds(minishell);
		if (minishell->data->pid_nbr > 0)
			minishell->data->return_value = wait_for_all(minishell);
	}
	// free_execution(minishell);
}

void	execute_builtin(t_minishell *minishell)
{
	if (ft_strncmp(minishell->command_line->command[0], "cd", 3) == 0)
		minishell->data->return_value = mini_cd(minishell);
	else if (ft_strncmp(minishell->command_line->command[0], "echo", 5) == 0)
		minishell->data->return_value = mini_echo(minishell);
	else if (ft_strncmp(minishell->command_line->command[0], "env", 4) == 0)
		minishell->data->return_value = mini_env(minishell);
	else if (ft_strncmp(minishell->command_line->command[0], "export", 7) == 0)
		minishell->data->return_value = mini_export(minishell);
	else if (ft_strncmp(minishell->command_line->command[0], "pwd", 4) == 0)
		minishell->data->return_value = mini_pwd();
	else if (ft_strncmp(minishell->command_line->command[0], "unset", 6) == 0)
		minishell->data->return_value = mini_unset(minishell);
	else if (ft_strncmp(minishell->command_line->command[0], "exit", 5) == 0)
		minishell->data->return_value = mini_exit(minishell);
}

static void close_fds(t_minishell *minishell)
{
	if (minishell->command_line == NULL)
		printf("t nul\n");
	while(minishell->command_line->prev)
		minishell->command_line = minishell->command_line->prev;
	while(minishell->command_line->next)
	{
		close(minishell->command_line->redirection->pipe[0]);
		close(minishell->command_line->redirection->pipe[1]);
		minishell->command_line = minishell->command_line->next;
	}
}

// WIFSIGNALED returns true if the child process was terminated by a signal.
// WTERMSIG returns the number of the signal that caused the child process to terminate.
// WEXITSTATUS returns the exit status of the child process.

static int wait_for_all(t_minishell *minishell)
{
    int index;
    int status;
    int last_status = 0;
    pid_t wait_pid;

    index = minishell->data->pid_nbr - 1;
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

// static void free_execution(t_minishell *minishell)
// {
// 	t_command_line *tmp;
// 	t_redirection *redir_tmp;
// 	while (minishell->command_line_head)
// 	{
// 		tmp = minishell->command_line_head;
// 		minishell->command_line_head = minishell->command_line_head->next;
// 		if(tmp->cmd_path)
// 			free(tmp->cmd_path);
// 		// if(tmp->command)
// 		// 	free_table(tmp->command);
// 		if(tmp->redirection)
// 		{
// 			while(tmp->redirection->next)
// 			{
// 				redir_tmp = tmp->redirection;
// 				tmp->redirection = tmp->redirection->next;
// 				free(tmp->redirection->input_file);
// 				free(tmp->redirection->output_file);
// 				free(tmp->redirection);
// 			}
// 			free(tmp->redirection);
// 		}
// 		free(redir_tmp);
// 		free(tmp);
// 	}
// }
/* Questions que je me suis posé */
	/* 
		Q:	Pourquoi je dois créé un pipe si il y a déja un outfile alors que bash priorise les outfile ?
		|
		R:	Il faut créer un pipe même avec un outfile car il permet la synchronisation des processus. Sans pipe, la commande suivante (comme cat) resterait bloquée en attente d'input sur STDIN.
			Le pipe, même vide, permet de signaler la fin de l'input quand il est fermé.
	*/