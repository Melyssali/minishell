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
    save_or_restore_fds(minishell, SAVE);
    while (minishell->command_line != NULL)
    {
        exec_loop(minishell);
        skip_and_free(minishell);
        save_or_restore_fds(minishell, RESTORE);
    }
    return(SUCCESS);
}

void save_or_restore_fds(t_minishell *minishell, int order)
{
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
}

int exec_loop(t_minishell *minishell)
{
    int fd_tab[2];

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
        if (exec_cmd(minishell, fd_tab) == FAIL)
            return(FAIL);
    return (SUCCESS);
}

int exec_cmd(t_minishell *minishell, int *pipe)
{
	pid_t	pid;

    if (build_cmd(minishell) == FAIL)
        return (FAIL);
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (FAIL);
    }
    if (pid == 0)
        child_process(minishell, pipe);
    else
        parent_process(minishell, pipe);
    return (SUCCESS);
}

void child_process(t_minishell *minishell, int *pipe)
{
    char **envp;

    envp = lst_to_arr(minishell->env);
    if (envp == NULL) 
    if (minishell->command_line->next != NULL)
    {
        close(pipe[0]);
        dup2(pipe[1], STDOUT_FILENO);
        close(pipe[1]);
    }
    if (execve(minishell->command_line->cmd_path, minishell->command_line->command, envp) == -1)
        perror("execve");
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

char **lst_to_arr(t_env_var *env)
{
    t_env_var *lst;
    char **dest;
    int i;
    int len;

    len = len_list(env);
    dest = (char **)malloc(sizeof(char *) * (len + 1));
    if (!dest)
        return (NULL);

    lst = env;
    i = 0;
    while (lst != NULL)
    {
        dest[i] = ft_strjoin_no_free(lst->key, "=");
        if (!dest[i])
        {
            free(dest);
            return (NULL);
        }
        char *full_str = ft_strjoin_no_free(dest[i], lst->value);
        free(dest[i]);
        if (!full_str)
        {
            free(dest);
            return (NULL);
        }
        dest[i] = full_str;
        lst = lst->next;
        i++;
    }
    dest[i] = NULL;
    return (dest);
}



int len_list(t_env_var *env)
{
    int len = 0;
    t_env_var *tmp = env;

    while (tmp != NULL)
    {
        len++;
        tmp = tmp->next;
    }
    return len;
}
