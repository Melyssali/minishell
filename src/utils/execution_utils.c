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

void skip_and_free(t_minishell *minishell)
{
	t_command_line *tmp;

	tmp = minishell->command_line;

	minishell->command_line = minishell->command_line->next;
	if(tmp->command)
		free_table(tmp->command);
	// if (tmp->input_file)
	// 	free(tmp->input_file);
	// if (tmp->output_file)
	// 	free(tmp->output_file);
	// if (tmp->heredoc_delimiter)
	// 	free(tmp->heredoc_delimiter);
	// if (tmp->heredoc_file)
	// 	free(tmp->heredoc_file);
	free(tmp);
}

int	execute_builtin(t_minishell *minishell)
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
	return(0);
}

void free_table(char **table)
{
    int i;

	i = -1;
    if (!table)
        return;
    while (table[++i] != NULL)
        free(table[i]);
    free(table);
	table = NULL;
}

void	init_struct(t_minishell *minishell, char **envp)
{
	minishell->envp = envp;
	copy_env(minishell);
	minishell->data = malloc(sizeof(t_data));
	if (!minishell->data)
	{
    	perror("malloc failed");
    	exit(EXIT_FAILURE);
	}
}
