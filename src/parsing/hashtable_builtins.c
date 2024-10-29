/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/29 13:36:14 by melyssa          ###   ########.fr       */
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

static void	insert(t_hash_builtins *table[], char *key)
{
	unsigned int	index;
	t_hash_builtins	*new_node;

	index = hash(key);
	new_node = malloc(sizeof(t_hash_builtins));
	new_node->key = ft_strdup(key);
	new_node->next = table[index];
	table[index] = new_node;
}

int	search(t_hash_builtins *table[], char *key)
{
	unsigned int	index;
	t_hash_builtins	*entry;

	index = hash(key);
	entry = table[index];
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
			return (1);
		entry = entry->next;
	}
	return (0);
}

void	initialize_builtins(t_hash_builtins *table_builtins[])
{
	insert(table_builtins, "echo");
	insert(table_builtins, "cd");
	insert(table_builtins, "pwd");
	insert(table_builtins, "env");
	insert(table_builtins, "unset");
	insert(table_builtins, "exit");
	insert(table_builtins, "export");
}
