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

void skip_cmd(t_command_line *command_line)
{
    t_command_line *tmp;

    if (!command_line)
        return;
    
    tmp = command_line;
    free(tmp->command);
    free(tmp->input_file);
    free(tmp->output_file);
    free(tmp->heredoc_delimiter);
    command_line = command_line->next;
    free(tmp);
}

int	execute_builtin(t_minishell *minishell)
{
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		minishell->data->return_value = mini_cd(minishell);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		minishell->data->return_value = mini_echo(minishell);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		minishell->data->return_value = mini_env(minishell);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		minishell->data->return_value = mini_export(minishell);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		minishell->data->return_value = mini_pwd(minishell);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		minishell->data->return_value = mini_unset(minishell);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		minishell->data->return_value = mini_exit(minishell);
}