/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/22 10:54:30 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_exit(char **cmd)
{
	if (ft_strcmp(cmd[0], "exit") == 0)
	{
		if (ft_count_args(cmd) > 2)
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		else
			exit(0);
	}
	return (1);
}