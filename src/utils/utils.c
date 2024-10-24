/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/24 11:35:50 by lscarcel         ###   ########.fr       */
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
	return (minishell->env);
}


int update_env_var(char *key, char *value, t_minishell *minishell)
{
    for (int i = 0; minishell->env[i] != NULL; i++)
    {
        if (strncmp(minishell->env[i], key, strlen(key)) == 0 && minishell->env[i][strlen(key)] == '=')
        {
            free(minishell->env[i]);
            minishell->env[i] = malloc(strlen(key) + strlen(value) + 2);
            if (!minishell->env[i])
                return (1);
            memcpy(minishell->env[i], key, strlen(key));
            minishell->env[i][strlen(key)] = '=';
            memcpy(minishell->env[i] + strlen(key) + 1, value, strlen(value) + 1);

            return (0);
        }
    }
    return (1);
}

void copy_env(t_minishell *minishell, char **envp)
{
	int i;
	size_t env_len;

	env_len = 0;
	i = 0;
	
	env_len = ft_count_args(envp);
	minishell->env = malloc(sizeof(char *) * (env_len + 1));
	if (!minishell->env)
		return ;
	while (envp != NULL)
	{
		minishell->env[i] = ft_strdup(envp[i]);
		i++;
	}
}