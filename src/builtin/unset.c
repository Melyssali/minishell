/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/04 11:28:35 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int mini_unset(char **cmd, t_minishell *minishell)
{
	t_env_var *ptr;
	t_env_var *prev;
	int i;

	i = -1;
	ptr = minishell->env;
	prev = NULL;
	while(cmd[++i] != NULL)
	{
		while(ptr != NULL && strcmp(ptr->value, cmd[i]) != 0)
		{
			prev = ptr;
			ptr = ptr->next;
		}
		if (ptr == NULL)
			return (0);
		if (prev == NULL)
			minishell->env = ptr->next;
		else
			prev->next = ptr->next;
		free(ptr->value);
		free(ptr);
	}
	return(0);
}