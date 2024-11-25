/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/24 13:50:48 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int mini_env(t_minishell *minishell)
{
	t_env_var *ptr;

	ptr = minishell->env;
	while (ptr != NULL)
	{
		printf("%s", ptr->key);
		printf("=");
		printf("%s\n", ptr->value);
		ptr = ptr->next;
	}
	return (0);
}
