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

void	ft_pwd(t_minishell *minishell)
{
	t_env_var *ptr;

	ptr = minishell->env;
	while (ptr != NULL)
	{
		if (strcmp(ptr->key, "PWD") == 0)
		{
			printf("%s=%s",ptr->key, ptr->value);
		}
		ptr = ptr->next;
	}
}
