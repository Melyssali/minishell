/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/27 19:47:20 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	handler_signal(int signum)
	{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_input(t_data *data, t_minishell *minishell, char *input)
{
	data->is_double_quotes = 1;
	data->tokens = split_into_tokens(input, data);
	if (data->tokens == NULL)
		printf("Syntax error: unclosed quotes.\n");
	if (data->is_double_quotes)
		data->tokens = handle_interpreting(data, minishell);
	if (data->tokens == NULL)
		printf("%d: command not found\n", minishell->data->return_value);
	else
	{
		if (classify_tokens(data))
		{
			free(data->token_types);
			minishell->command_line_head = parsing(data);
			if (minishell->command_line_head == NULL)
			{
				printf("Error: ptr is NULL, linked list is empty.\n");
				return ;
			}
			free_arr_tokenization(data->tokens);
		}
		execution(minishell);
		// free_nodes_parsing(minishell->command_line);
	}
}

static void	initialize_data(t_data *data, t_minishell *minishell, char **envp)
{
	initialize_table(data->table_op, data->table_builtins);
	initialize_operators(data->table_op);
	initialize_builtins(data->table_builtins);
	init_struct(minishell, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;
	t_minishell	minishell;
	char		*input;

	(void)argc;
	(void)argv;
	initialize_data(&data, &minishell, envp);
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell % ");
		if (input == NULL)
			break ;
		if (input[0] != '\0')
		{
			add_history(input);
			handle_input(&data, &minishell, input);
		}
		free(input);
		return(minishell.data->return_value);
	}
	free_all_parsing(minishell.command_line, data.table_op, data.table_builtins);
	return (0);
}
