/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/22 15:16:28 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int    ft_pwd(char **cmd)
{
    char	cwd[10000];
    
	if (ft_strcmp(cmd[0], "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
            return(0);
		}
		else
		{
			perror("pwd");
            return(1);
		}
	}
	return(1);
}
