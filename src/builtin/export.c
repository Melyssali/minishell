/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/23 13:35:06 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int mini_export(t_minishell *minishell)
{
	if (minishell->command_line->command[1] != NULL)
	{
		char *equal_sign = strchr(minishell->command_line->command[1], '=');
		if (equal_sign != NULL)
		{
			int key_length = equal_sign - minishell->command_line->command[1];
			char *key = strndup(minishell->command_line->command[1], key_length);
			if (ft_getenv(key, minishell))
				update_env_value(key, minishell->command_line->command[1], minishell);
			else
				add_node(minishell->command_line->command[1], minishell);
			free(key);
		}
		return(0);
	}
	else
		declare(minishell);
	return(0);
}

void	declare(t_minishell *minishell)
{
	t_env_var *ptr;

	ptr = minishell->env;
	while (ptr != NULL)
	{
		printf("declare -x ");
		printf("%s", ptr->key);
		printf("=");
		printf("\"");
		printf("%s\n", ptr->value);
		printf("\"");
		ptr = ptr->next;
	}
}
