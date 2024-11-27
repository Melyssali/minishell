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

int mini_cd(t_minishell *minishell)
{
	char cwd[10000];

	if (chdir(minishell->command_line->command[1]) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			update_env_value("PWD", cwd, minishell);	
			return(0);
		}
		else 
		{
			printf("minishell : cd : %s: No such file or directory", minishell->command_line->command[1]);
			return(1);			
		}
	}
	return(0);
}
