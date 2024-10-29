/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/28 21:49:42 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

unsigned int	hash(char *str)
{
	unsigned int	hash;

	hash = 0;
	while (*str)
	{
		hash = (hash << 5) + *str;
		str++;
	}
	return (hash % HASH_TABLE_SIZE);
}
void	insert(t_builtin **table, char *key)
{
	unsigned int	index;
	t_builtin *new_node;

	index = hash(key);
	new_node = malloc(sizeof(t_builtin));
	new_node->key = ft_strdup(key);
	new_node->next = table[index];
	table[index] = new_node;
}

int search(t_builtin **table, char *key)
{
    unsigned int index;
    t_builtin *entry;
	
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

void initialize_builtins(t_builtin **hash_table)
{
    insert(hash_table, "echo");
    insert(hash_table, "cd");
    insert(hash_table, "pwd");
    insert(hash_table, "env");
    insert(hash_table, "unset");
    insert(hash_table, "exit");
    insert(hash_table, "export");
}


