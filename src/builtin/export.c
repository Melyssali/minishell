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

int export(char **cmd, t_minishell *minishell)
{
	if (cmd[1] != NULL)
	{
		char *equal_sign = strchr(cmd[1], '=');
		if (equal_sign != NULL)
		{
			int key_length = equal_sign - cmd[1];
			char *key = strndup(cmd[1], key_length);
			if (ft_getenv(key, minishell))
				update_env_value(key, cmd[1], minishell);
			else
				add_node(cmd[1], minishell);
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
