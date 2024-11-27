/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/20 22:08:37 by melyssa          ###   ########.fr       */
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
int	main(int argc, char **argv, char**envp)
{
	(void)argc;
	(void)argv;
	// (void)envp;
	t_data data;
	// t_env_var env;
	t_minishell minishell;
	char *input;

	initialize_table(data.table_op, data.table_builtins);
	initialize_operators(data.table_op);
	initialize_builtins(data.table_builtins);
	init_struct(&minishell, envp);
	signal(SIGINT, handler_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell % ");
		if (input == NULL)
		{
			printf("bye.\n");
			break ;
		}
		add_history(input);
		data.tokens = split_into_tokens(input);
		if (data.tokens == NULL)
			printf("Syntax error: unclosed quotes.\n");
		data.tokens = handle_interpreting(&data, &minishell);
		if (data.tokens == NULL)
			printf("%d\n", errno);
		else
		{
			if (ft_strcmp(data.tokens[0], "exit") == 0)
				exit(EXIT_SUCCESS);
			if (classify_tokens(&data))
			{
				minishell.command_line = parsing(&data);
				if (minishell.command_line == NULL)
				{
					printf("Error: ptr is NULL, linked list is empty.\n");
					return (1);
				}
			}
			execution(&minishell);
		}
	}
	return (0);
}
