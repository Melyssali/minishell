/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/22 15:28:13 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_count_args(char **cmd)
{
    int i;

    i = 0;
    while (cmd[i] != NULL)
        i++;
    return (i);
}

char	*ft_getenv(char *var, t_minishell *minishell)
{
	while (ft_strncmp(var, minishell->env, 5))
		minishell->env++;
	return (minishell->env + 5);
}