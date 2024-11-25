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
    while (minishell->command_line != NULL)
    {
        setup_redirections(minishell->command_line);
        if (minishell->command_line->is_builtin == TRUE)
            execute_builtin(minishell);
        // else
            // exec_cmd(minishell->command_line.cmd);
        skip_cmd(minishell);
    }
    // if(minishell->data.pipe_nbr > 1)
    // 	wait_every_thread(t_minishell *minishell);
    return(0);
}  