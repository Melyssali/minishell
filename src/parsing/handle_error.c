/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/20 22:08:37 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//  PIPE > NOTHING = ERROR
// erreur ->tu t'prends pour zuckerberg ? t sur MIINISHELL pas sur shell,
// non mais on est ou la
// GERER < file.txt cat
//  > file.txt | grep "test"
// if !COMMAND -> If PIPE ? DO something : PROMPT to someone
//  
// 	•	Un opérateur | ne doit pas être le dernier token de la commande.
// 	•	Un opérateur > ou >> doit être suivi d’un nom de fichier valide.
// 	•	Un opérateur < doit être suivi d’un nom de fichier valide.
// 	•	Un opérateur | doit être entouré de commandes valides.

// une commande doit être suivi d'un argument file.txt "qqchose" ou - ou --
// pipe doit toujours être suivi d'une commande
//  redirection < ou > doit toujours être suivi d'un fichier
//  > doit être précédé d'une commande valide

// ls > file.txt | grep cd "test"

int	classify_tokens(t_data *data)
{
	int	i;
	int	arr_length;
	int	operator_type;
	int	builtin_type;

	i = 0;
	arr_length = calculate_array_length(data->tokens);
	data->previous_state = -2;
	data->token_types = malloc(sizeof(int) * arr_length);
	while (data->tokens[i])
	{
		operator_type = get_operator_type(data->table_op, data->tokens[i]);
		builtin_type = search(data->table_builtins, data->tokens[i]);
		if (operator_type != -1)
		{
			if (i == 0 && operator_type == PIPE)
			{
				printf("Syntax error near unexpected token `|'\n");
				return (0);
			}
			data->token_types[i] = OPERATOR;
			data->previous_op_state = operator_type;
		}
		else if (i == 0 || builtin_type != -1
			|| (data->previous_state == OPERATOR
				&& data->previous_op_state == PIPE && data->tokens[i][0] != '\0'))
		{
			data->token_types[i] = COMMAND;
		}
		else if (data->previous_state == OPERATOR &&
				(data->previous_op_state >= REDIR_OUTPUT && data->previous_op_state <= HEREDOC) && data->tokens[i][0] != '\0')
			data->token_types[i] = ARGUMENT_FILE;
		else if (data->previous_state == COMMAND && handle_operators_error(data->tokens[i]))
			data->token_types[i] = ARGUMENT;
		else
		{
			printf("Syntax error\n");
			return (0);
		}
		data->previous_state = data->token_types[i];
		i++;
	}
	return (handle_error(data->token_types));
}

int	handle_error(int *token_types)
{
	int	i;

	i = 0;
	while (token_types[i])
	{
		if (token_types[i] == COMMAND && token_types[i + 1] == COMMAND)
		{
			printf("Syntax error. Cmd can't be followed by cmd\n");
			return (0);
		}
		else if (token_types[i] == OPERATOR && token_types[i + 1] == OPERATOR)
		{
			printf("Syntax error. Double operators\n");
			return (0);
		}
		else if (token_types[i] == OPERATOR)
		{
			if (!token_types[i + 1] || (token_types[i + 1] != ARGUMENT
					&& token_types[i + 1] != ARGUMENT_FILE && token_types[i
					+ 1] != COMMAND))
			{
				printf("Syntax error near unexpected token `newline'\n");
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	handle_operators_error(char *s)
{
	while (*s)
	{
		if (*s == '<')
		{
			if ((*(s + 1) && *(s + 1) != '<') || (*(s - 1) && *(s - 1) != '<'))
			{
				printf("Syntax error. Double operators\n");
				return (0);
			}
		}
		else if (*s == '>')
		{
			if ((*(s + 1) && *(s + 1) != '>') || (*(s - 1) && *(s - 1) != '>'))
			{
				printf("Syntax error. Double operators\n");
				return (0);
			}
		}
		else if (*s == '|' && *(s + 1) && *(s + 1) == '|')
		{
			printf("Syntax error. Double operators\n");
			return (0);
		}
		s++;
	}
	return (1);
}
