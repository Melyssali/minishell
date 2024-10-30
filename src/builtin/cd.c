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

void cd_error(char **cmd)
{
	printf("minishell : cd : %s: No such file or directory", cmd[1]);
}

int mini_cd(char **cmd, t_minishell *minishell)
{
    char cwd[10000];
	
    if (chdir(cmd[1]) == 0)
    {
    	if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
			update_env_var("PWD", cwd, minishell);	
            return(0);
		}
        else 
		{
        	cd_error(cmd);
			return(1);			
		}
    }
	return(0);
}
