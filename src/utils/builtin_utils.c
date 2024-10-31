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

char *ft_getenv(char *key, t_minishell *minishell)
{
    t_env_var *ptr;

    ptr = minishell->env;
    while (ptr != NULL)
    {
        if (strcmp(ptr->key, key) == 0)
            return (ptr->value);
        ptr = ptr->next;
    }
    return (NULL);
}


int update_env_value(char *key, char *value, t_minishell *minishell)
{
    t_env_var *ptr;

    ptr = minishell->env;
    while (ptr != NULL)
    {
        if (strcmp(ptr->key, key) == 0)
        {
            free(ptr->value);
            ptr->value = malloc(strlen(value) + 1);
            if (!ptr->value)
                return (1);
            strcpy(ptr->value, value);
            return (0);
        }
        ptr = ptr->next;
    }
    return (1);
}

void copy_env(t_minishell *minishell)
{
    int i;
    int j;
    t_env_var *node;
    t_env_var *tmp;

    i = -1;
    while(minishell->envp[++i])
    {
        node = (t_env_var *)malloc(sizeof(t_env_var));
        if (!node)
            return;
    	j = 0;
        while(minishell->envp[i][j] != '=')
			j++;
		node->key = strndup(minishell->envp[i], j);
		node->value = strdup(minishell->envp[i] + j + 1);
		if (node->value == NULL)
            return;
		if (i == 0)
		{
			tmp = node;
			minishell->env = node;
		}
		else 
		{
			tmp->next = node;
			tmp = node;
		}
    }
    node->next = NULL;
}

int add_node(char *str, t_minishell *minishell)
{
	t_env_var *node;
	t_env_var *last;
	int i;

	i = 0;
	node = (t_env_var *)malloc(sizeof(t_env_var));
    if (!node)
        return(0);
	while(str[i] && str[i] != '=')
		i++;
	node->key = strndup(str, i);
    if (str[i] == '=')
    {
        node->value = strdup(str + i + 1);
        if (!node->value)
            return(0);
    }
    else
        node->value = NULL;
	node->next = NULL;
    last = minishell->env;
    while (last->next)
        last = last->next;
    last->next = node;
    return 0;
}

