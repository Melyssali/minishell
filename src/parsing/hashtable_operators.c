/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_op.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/20 22:07:03 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static unsigned int	hash(char *str)
{
	unsigned int	hash;

	hash = 5381;
	while (*str)
	{
		hash = ((hash << 5) + hash) + *str;
		str++;
	}
	return (hash % TABLE_OP_SIZE);
}

static void	insert(t_hash_operators *table_op[], char *key, int type)
{
	unsigned int		index;
	t_hash_operators	*new_node;

	index = hash(key);
	new_node = malloc(sizeof(t_hash_operators));
	new_node->key = ft_strdup(key);
	new_node->type = type;
	new_node->next = table_op[index];
	table_op[index] = new_node;
}

int	get_operator_type(t_hash_operators *table_op[], char *str)
{
	t_hash_operators	*ptr;
	int					index;

	index = hash(str);
	ptr = table_op[index];
	while (ptr)
	{
		if (ft_strcmp(ptr->key, str) == 0)
			return (ptr->type);
		ptr = ptr->next;
	}
	return (-1);
}

void	initialize_operators(t_hash_operators *table_op[])
{
	insert(table_op, ">", REDIR_OUTPUT);
	insert(table_op, ">>", APPEND_OUTPUT);
	insert(table_op, "<", REDIR_INPUT);
	insert(table_op, "<<", HEREDOC);
	insert(table_op, "|", PIPE);
}
