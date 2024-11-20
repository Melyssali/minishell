/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/20 12:57:23 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
#include "libft.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>

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
int	main(void)
{
	t_data data;
	t_command_line *ptr;
	char *input;
	char **tokens;
	
	initialize_table(data.table_operators, data.table_builtins);
	initialize_operators(data.table_operators);
	initialize_builtins(data.table_builtins);
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
		tokens = split_into_tokens(input);
		if (tokens == NULL)
			printf("Problem with quotes.\n");
		else
		{
			if (ft_strcmp(tokens[0], "exit") == 0)
				exit(EXIT_SUCCESS);
			if (classify_tokens(tokens, &data))
			{
				ptr = parsing(tokens, &data);
				if (ptr == NULL)
				{
					printf("Error: ptr is NULL, linked list is empty.\n");
					return (1);
				}
				printf("pipe count : %d\n", data.pipe_count);
			}
		}
	}
	return (0);
}
