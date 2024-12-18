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

void export_error(char *str)
{
	print_error("minishell: export: ");
	print_error(str);
	print_error(": not a valid identifier\n");
}
int arg_check(char *arg)
{
	int i;

	i = 0;
	if (arg[0] == '=' || (!ft_isalpha(arg[0]) && arg[0] != '_'))
	{
		export_error(arg);
		return (FAIL);
	}
	i++;
	while(arg[i] != '=' && arg[i])
	{
		if (!ft_isalnum(arg[i]))
		{
			export_error(arg);
			return (FAIL);
		}
		i++;
	}
	return(SUCCESS);
}
int	mini_export(t_minishell *minishell)
{
	int		key_len;
	char	*equal_sign;

	if (minishell->command_line->command[1] != NULL)
	{
		if (arg_check(minishell->command_line->command[1]) == FAIL)
			return (FAIL);
		equal_sign = strchr(minishell->command_line->command[1], '=');
		key_len = equal_sign - minishell->command_line->command[1];
		if (equal_sign != NULL)
			return (change_value(minishell, equal_sign, key_len));
		else
			return (SUCCESS);
	}
	else
		declare(minishell);
	return (SUCCESS);
}

int	change_value(t_minishell *minishell, char *equal_sign, int key_len)
{
	char	*value;
	char	*key;

	key = strndup(minishell->command_line->command[1], key_len);
	if (!key)
		return (FAIL);
	if (ft_getenv(key, minishell))
	{
		if (ft_strlen(equal_sign) == 0)
			update_env_value(key, NULL, minishell);
		else
		{
			value = strdup(equal_sign + 1);
			if (!value)
				return (FAIL);
			update_env_value(key, value, minishell);
		}
	}
	else
		add_node(minishell->command_line->command[1], minishell);
	free(key);
	return (SUCCESS);
}

void	declare(t_minishell *minishell)
{
	t_env_var	*ptr;

	ptr = minishell->env;
	while (ptr != NULL)
	{
		printf("declare -x ");
		printf("%s", ptr->key);
		printf("=");
		printf("\"");
		printf("%s", ptr->value);
		printf("\"\n");
		ptr = ptr->next;
	}
}
