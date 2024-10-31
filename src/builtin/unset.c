/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/12 12:22:51 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void mini_unset(char **cmd, t_minishell *minishell)
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
			return ;
		if (prev == NULL)
			minishell->env = ptr->next;
		else
			prev->next = ptr->next;
		free(ptr->value);
		free(ptr);
	}
}