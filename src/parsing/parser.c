/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/28 21:45:28 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

// ls -l | grep ".txt" > output.txt
// ls -l | echo "hello"
// ls, -l, |, echo, "hello", NULL
// ls, -l, >, echo, "hello", NULL
//  0   1  2    3      4
// we check if it's a builtin or not -> this func return 1 or 0 (true or false)
// implement a hash table
int	is_builtin_command(char *cmd, t_builtin **hash_table)
{
	return (search(hash_table, cmd));
	
	// return (strcmp(cmd, "echo") == 0 || strcmp(cmd, "cd") == 0 || strcmp(cmd,
	// 		"pwd") == 0 || strcmp(cmd, "export") == 0 ||  strcmp(cmd, "unset") == 0 ||
	// 		 strcmp(cmd, "env") == 0 || strcmp(cmd, "exit") == 0);
}
// if Pipe, we create nodes to link two commands or more
// strdup(tokens[++i]); -> j'incremente i (++i) et apres je strdup
// gestion erreur : ls > touch "file.txt" ne fonctionne pas car une redirection peut pas se faire
// sur un executable

//  checker les erreurs
// si y'a quelque chose avant le pipe, ça fonctionne pas parce qu'il ne rentre jamais dans !new_node 
t_command_line	*parsing(char **tokens)
{
	t_command_line	*head;
	t_command_line	*current;
	t_command_line	*new_node;
	// est-ce que je peux declarer comme ça ?
	t_builtin 		*hash_table[HASH_TABLE_SIZE] = {NULL};
	int				i;

	head = NULL;
	current = NULL;
	new_node = NULL;
	i = 0;
	initialize_builtins(hash_table);
	new_node = create_node(tokens, &i, hash_table);
	if (!head)
		head = new_node;
	current = new_node;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], REDIR_OUTPUT) == 0 || ft_strcmp(tokens[i], APPEND_OUTPUT) == 0)
		{
			new_node->append_output = (ft_strcmp(tokens[i], APPEND_OUTPUT) == 0);
			new_node->output_file = ft_strdup(tokens[++i]);
		}
		else if (ft_strcmp(tokens[i], REDIR_INPUT) == 0)
		{
			new_node->input_file = ft_strdup(tokens[++i]);
		}
		else if (ft_strcmp(tokens[i], HEREDOC) == 0)
		{
			new_node->heredoc_delimiter = ft_strdup(tokens[++i]);
		}
		else if (ft_strcmp(tokens[i], PIPE) == 0)
		{
			i++;
			new_node = create_node(tokens, &i, hash_table);
			current->next = new_node;
			current = new_node;
			i--;
		}
		i++;
	}
	return (head);		
}

