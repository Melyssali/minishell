/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/05 10:02:37 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//si un builtin est trouvé par is_builtin, exec_builtin est utilisé


int exec_builtin(t_minishell *minishell);
{
    if(minishell-­>command_line->builtin_type == ECHO)
        // minishell-­>data->exit_code == mini_echo(minishell);
    else if(minishell-­>command_line->builtin_type == CD)
        // minishell-­>data->exit_code == mini_cd(minishell);
    else if(minishell-­>command_line->builtin_type == ENV)
        // minishell-­>data->exit_code == mini_env(minishell);
    else if(minishell-­>command_line->builtin_type == EXIT)
        // minishell-­>data->exit_code == mini_exit(minishell);
    else if(minishell-­>command_line->builtin_type == EXPORT)
        // minishell-­>data->exit_code == mini_export(minishell);
    else if(minishell-­>command_line->builtin_type == PWD)
        // minishell-­>data->exit_code == mini_pwd(minishell);
    else if(minishell-­>command_line->builtin_type == UNSET)
        // minishell-­>data->exit_code == mini_unset(minishell);  
}

// ptr = parsing(blabla);
// 	t_command_line *tmp = ptr;
// 		while (tmp)
// 		{
// 			for (int i = 0; tmp->command[i]; i++)
// 				do something
// 			if (tmp->is_builtin)
// 				exec_builtin(tmp->builtin_type);
//             else
//                 execve(tmp->cmd[]);
// 			if (tmp->input_file)
// 				exec_input(params);
// 			if (tmp->output_file)
// 				exec_output(params);
// 			etc
// 			tmp = tmp->next;
// 		}

< file.txt | grep "test"