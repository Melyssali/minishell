/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/05 20:05:04 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


// This file processes the input and creates a linked list to pass to the execution part

int	is_builtin_command(char *cmd, t_hash_builtins *table_builtins[])
{
	return (search(table_builtins, cmd));
}
// strdup(tokens[++i]); -> j'incremente i (++i) et apres je strdup
// gestion erreur : ls > touch "file.txt" ne fonctionne pas car une redirection peut pas se faire
// sur un executable

// Je dois découper cette fonction :
// GERER   < ls | wc -l
//  ls > test ok -- output ecrit que "test" et pas test ok
// ls > suivi d'un espace
t_command_line	*parsing(char *tokens[], t_data *data)
{
	t_command_line		*head;
	t_command_line		*current;
	t_command_line		*new_node;
	int					i;
	int					operator_type;

	head = NULL;
	current = NULL;
	new_node = NULL;
	data->pipe_count = 0;
	i = 0;
	// initialize_builtins(data->table_builtins);
	// initialize_operators(data->table_operators);
	new_node = create_node(data->table_operators, tokens, &i, data->table_builtins);
	if (!head)
		head = new_node;
	current = new_node;
	while (tokens[i])
	{
		operator_type = get_operator_type(data->table_operators, tokens[i]);
		printf("function : Parsing. operator type : %d\n", operator_type);
		printf("function : Parsing. INDEX: %d\n", i);
		if (operator_type == REDIR_OUTPUT || operator_type == APPEND_OUTPUT)
		{
			new_node->append_output = (operator_type == APPEND_OUTPUT);
			new_node->output_file = ft_strdup(tokens[++i]);
		}
		else if (operator_type == REDIR_INPUT)
		{
			new_node->input_file = ft_strdup(tokens[++i]);
		}
		else if (operator_type == HEREDOC)
		{
			new_node->heredoc_delimiter = ft_strdup(tokens[++i]);
		}
		else if (operator_type == PIPE)
		{
			i++;
			new_node = create_node(data->table_operators, tokens, &i, data->table_builtins);
			current->next = new_node;
			current = new_node;
			data->pipe_count++;
			i--;
		}
		i++;
	}
	return (head);
}
