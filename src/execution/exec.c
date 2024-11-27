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

int execution(t_minishell *minishell)
{
    if (check_file_access(minishell) == FAIL)
        skip_cmd(minishell);
    save_or_restore_fds(minishell, SAVE);
    while (minishell->command_line != NULL)
        {
            if (exec_loop(minishell) == FAIL)
                skip_cmd(minishell);
        }
    clean_up_node(minishell->command_line);
    return(0);
}


int save_or_restore_fds(t_minishell *minishell, int order)
{
    if (!minishell->data)
    {
        fprintf(stderr, "Error: minishell->data is not initialized.\n");
        exit(EXIT_FAILURE);
    }
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
    return(0);
}

int exec_loop(t_minishell *minishell)
{
    int return_value;
    int pipe[2];

    return_value = SUCCESS;
    if (setup_redirections(minishell->command_line, pipe) == FAIL)
    {
        skip_cmd(minishell);
        return_value = FAIL;
    }
    if (minishell->command_line->is_builtin == TRUE)
        execute_builtin(minishell);
    else
        exec_cmd(minishell, pipe);
    skip_cmd(minishell);
    save_or_restore_fds(minishell, RESTORE);
    return (return_value);
}

int exec_cmd(t_minishell *minishell, int *pipe)
{
	pid_t	pid;

    if (build_cmd(minishell) == FAIL)
        return (FAIL);
    pid = fork();
    if(pid == -1)
        perror("fork");
    if (pid == 0)
        child_process(minishell, pipe);
    else
        parent_process(minishell, pipe);
    return (0);
}

void child_process(t_minishell *minishell, int *pipe)
{
    if (minishell->command_line->next != NULL)
    {
        close(pipe[0]);
        dup2(pipe[1], STDOUT_FILENO);
        close(pipe[1]);
    }
    execve(minishell->command_line->cmd_path, minishell->command_line->command, minishell->envp);
    perror("execve");
    exit(1);
}

void parent_process(t_minishell *minishell, int *pipe)
{
    if (minishell->command_line->next != NULL)
    {
        close(pipe[1]);
        dup2(pipe[0], STDIN_FILENO);
        close(pipe[0]);
    }
    waitpid(-1, &minishell->data->return_value, 0);
}

void    clean_up_node(t_command_line *command_line)
{
    free_table(command_line->command);
    free(command_line->input_file);
    free(command_line->output_file);
    free(command_line->cmd_path);
    free(command_line);
}