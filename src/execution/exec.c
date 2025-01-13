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

static void cmd_child(t_minishell *minishell)
{
	char	**envp;

	envp = lst_to_arr(minishell->env);
	if (!envp)
		return ; // need to free
	pipe_redir(minishell);
	if (file_redir(minishell->command_line) == FAIL)
	{
		minishell->data->return_value = FAIL;
		return ;
	}
	if (build_cmd(minishell) == FAIL)
		exit(127);
	if (execve(minishell->command_line->cmd_path,
			minishell->command_line->command, envp) == -1)
		perror("execve");
}
static int single_builtin(t_minishell *minishell)
{
	if (file_redir(minishell->command_line) == FAIL)
	{
		minishell->data->return_value = FAIL;
		return (1);
	}
	execute_builtin(minishell);
	// free_execution;
	return (0);
}

static void single_cmd(t_minishell *minishell)
{
	pid_t single_pid;

	single_pid = fork();
	if (single_pid == -1)
	{
		perror("fork");
		return ;
	}
	if (single_pid == 0)
		cmd_child(minishell);
	else
		waitpid(single_pid, NULL, 0);
}

static void builtin_child(t_minishell *minishell)
{
	pipe_redir(minishell);
	if (file_redir(minishell->command_line) == FAIL)
	{
		minishell->data->return_value = FAIL;
		return ;
	}
	fprintf(stderr,"open : %d", minishell->command_line->redirection->pipe[1]);
	fprintf(stderr,"open : %d", minishell->command_line->redirection->pipe[0]);
	execute_builtin(minishell);
	exit(1);
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

static int need_fork(t_minishell *minishell, int count)
{
	t_command_line *head;

	head = minishell->command_line;
	minishell->data->pid_table = malloc(sizeof(pid_t) * minishell->data->pipe_count + 1);
	while(count > 0)
	{
		if(minishell->command_line->next)
		{
			if (pipe(minishell->command_line->redirection->pipe) == -1)
			{
				perror("pipe");
				return (FAIL);	
			}
		}
		minishell->data->pid_table[minishell->data->pid_nbr] = fork();
		if (minishell->data->pid_table[minishell->data->pid_nbr] == -1)
		{
			perror("fork");
			return (FAIL);
		}
		if (minishell->data->pid_table[minishell->data->pid_nbr] == 0)
		{
			if(minishell->command_line->is_builtin == TRUE)
				builtin_child(minishell);
			else
				cmd_child(minishell);
		}
		minishell->data->pid_nbr++;
		count--;
		minishell->command_line = minishell->command_line->next;
	}
	minishell->command_line = head;
	close_fds(minishell);
	if (minishell->data->pid_nbr > 0)
		minishell->data->return_value = wait_for_all(minishell);
	return (0);
}

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
		if (minishell->command_line->is_builtin == TRUE)
			single_builtin(minishell);
		else
			single_cmd(minishell);
	}
	else
		need_fork(minishell, count);
}

/* Questions que je me suis posé */
	/* 
		Q:	Pourquoi je dois créé un pipe si il y a déja un outfile alors que bash priorise les outfile ?
		|
		R:	Il faut créer un pipe même avec un outfile car il permet la synchronisation des processus. Sans pipe, la commande suivante (comme cat) resterait bloquée en attente d'input sur STDIN.
			Le pipe, même vide, permet de signaler la fin de l'input quand il est fermé.
	*/