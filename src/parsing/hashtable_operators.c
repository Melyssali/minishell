/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_operators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/04 22:59:59 by melyssa          ###   ########.fr       */
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
	return (hash % TABLE_OPERATORS_SIZE);
}

static void	insert(t_hash_operators *table_operators[], char *key,
		int type)
{
	unsigned int		index;
	t_hash_operators	*new_node;

	index = hash(key);
	new_node = malloc(sizeof(t_hash_operators));
	new_node->key = ft_strdup(key);
	new_node->type = type;
	new_node->next = table_operators[index];
	table_operators[index] = new_node;
}

int	get_operator_type(t_hash_operators *table_operators[], char *str)
{
	t_hash_operators	*ptr;
	int					index;

	index = hash(str);
	ptr = table_operators[index];
	while (ptr)
	{
		if (ft_strcmp(ptr->key, str) == 0)
			return (ptr->type);
		ptr = ptr->next;
	}
	return (-1);
}

void	initialize_operators(t_hash_operators *table_operators[])
{
	insert(table_operators, ">", REDIR_OUTPUT);
	insert(table_operators, ">>", APPEND_OUTPUT);
	insert(table_operators, "<", REDIR_INPUT);
	insert(table_operators, "<<", HEREDOC);
	insert(table_operators, "|", PIPE);
}