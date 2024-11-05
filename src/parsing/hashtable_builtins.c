/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/04 21:13:37 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

static unsigned int	hash(char *str)
{
	unsigned int	hash;

	hash = 0;
	while (*str)
	{
		hash = (hash << 5) + *str;
		str++;
	}
	return (hash % TABLE_BUILTINS_SIZE);
}

static void	insert(t_hash_builtins *table[], char *key, int type)
{
	unsigned int	index;
	t_hash_builtins	*new_node;

	index = hash(key);
	new_node = malloc(sizeof(t_hash_builtins));
	new_node->key = ft_strdup(key);
	new_node->type = type;
	new_node->next = table[index];
	table[index] = new_node;
}

int	search(t_hash_builtins *table[], char *key)
{
	unsigned int	index;
	t_hash_builtins	*ptr;

	index = hash(key);
	ptr = table[index];
	while (ptr)
	{
		if (ft_strcmp(ptr->key, key) == 0)
			return (ptr->type);
		ptr = ptr->next;
	}
	return (-1);
}

void	initialize_builtins(t_hash_builtins *table_builtins[])
{
	insert(table_builtins, "echo", ECHO);
	insert(table_builtins, "cd", CD);
	insert(table_builtins, "pwd", PWD);
	insert(table_builtins, "env", ENV);
	insert(table_builtins, "unset", UNSET);
	insert(table_builtins, "exit", EXIT);
	insert(table_builtins, "export", EXPORT);
}
