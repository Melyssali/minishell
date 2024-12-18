/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/08 21:23:30 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	handle_tokens(t_data *data, int builtin_type, int operator_type,
		int i)
{
	if (operator_type != -1 && handle_operators_error(data->tokens[i]))
	{
		if (i == 0 && operator_type == PIPE)
		{
			printf("Syntax error near unexpected token `|'\n");
			return (0);
		}
		data->token_types[i] = OPERATOR;
		data->previous_op_state = operator_type;
	}
	else if (i == 0 || builtin_type != -1 || (data->previous_state == OPERATOR
			&& data->previous_op_state == PIPE && data->tokens[i][0] != '\0'))
	{
		data->token_types[i] = COMMAND;
	}
	else if (data->previous_state == OPERATOR
		&& (data->previous_op_state >= REDIR_OUTPUT
			&& data->previous_op_state <= HEREDOC)
		&& data->tokens[i][0] != '\0')
		data->token_types[i] = ARGUMENT_FILE;
	else if (data->previous_state == COMMAND)
		data->token_types[i] = ARGUMENT;
	return (1);
}

int	classify_tokens(t_data *data)
{
	int	i;
	int	arr_length;
	int	operator_type;
	int	builtin_type;
	int	return_value;

	i = 0;
	arr_length = calculate_array_length(data->tokens);
	data->previous_state = -2;
	data->token_types = malloc(sizeof(int) * arr_length);
	while (data->tokens[i])
	{
		operator_type = get_operator_type(data->table_op, data->tokens[i]);
		builtin_type = search(data->table_builtins, data->tokens[i]);
		return_value = handle_tokens(data, builtin_type, operator_type, i);
		if (!return_value)
			return (0);
		data->previous_state = data->token_types[i];
		i++;
	}
	return (handle_error(data->token_types));
}

int	handle_error(int *token_types)
{
	int		i;
	char	*msg_error;

	msg_error = NULL;
	i = -1;
	while (token_types[++i])
	{
		if (token_types[i] == COMMAND && token_types[i + 1] == COMMAND)
			msg_error = "Syntax error. Cmd can't be followed by cmd\n";
		else if (token_types[i] == OPERATOR && token_types[i + 1] == OPERATOR)
			msg_error = "Syntax error. Double operators\n";
		else if (token_types[i] == OPERATOR)
		{
			if (!token_types[i + 1] || (token_types[i + 1] != ARGUMENT
					&& token_types[i + 1] != ARGUMENT_FILE && token_types[i + 1]
					!= COMMAND))
				msg_error = "Syntax error near unexpected token `newline'\n";
		}
		if (msg_error)
		{
			printf("%s", msg_error);
			return (0);
		}
	}
	return (1);
}

int	handle_operators_error(char *s)
{
	char	*msg_error;

	msg_error = NULL;
	while (*s)
	{
		if (*s == '<')
		{
			if ((*(s + 1) && *(s + 1) != '<') || (*(s - 1) && *(s - 1) != '<'))
				msg_error = "Syntax error. Double operators\n";
		}
		else if (*s == '>')
		{
			if ((*(s + 1) && *(s + 1) != '>') || (*(s - 1) && *(s - 1) != '>'))
				msg_error = "Syntax error. Double operators\n";
		}
		else if (*s == '|' && *(s + 1) && *(s + 1) == '|')
			msg_error = "Syntax error. Double operators\n";
		if (msg_error)
		{
			printf("%s", msg_error);
			return (0);
		}
		s++;
	}
	return (1);
}
