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

/*-------------------Prototypes----------------------*/
void extern_cmd_child(t_minishell *minishell);
static void builtin_child(t_minishell *minishell);
static int exec_loop(t_minishell *minishell);
/*---------------------------------------------------*/

int pipeline_cmd(t_minishell *minishell, int count)
{
	t_command_line *head;

	head = minishell->command_line;
	minishell->data->pid_table = malloc(sizeof(pid_t) * minishell->data->pipe_count + 1);
	while(count > 0)
	{
        if(exec_loop(minishell) == FAIL)
            return (FAIL);
		minishell->data->pid_nbr++;
		count--;
		minishell->command_line = minishell->command_line->next;
	}
	minishell->command_line = head;
	return (0);
}

static int exec_loop(t_minishell *minishell)
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
            extern_cmd_child(minishell);
    }
    return (SUCCESS);
}

void extern_cmd_child(t_minishell *minishell)
{
	char	**envp;

	envp = lst_to_arr(minishell->env);
	pipe_redir(minishell);
	if (file_redir(minishell->command_line) == FAIL)
	{
		minishell->data->return_value = FAIL;
		return ;
	}
	if (build_path(minishell) == FAIL)
		exit(127);
	if (execve(minishell->command_line->cmd_path,
			minishell->command_line->command, envp) == -1)
		perror("execve");
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