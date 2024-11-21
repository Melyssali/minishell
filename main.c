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
	// t_env_var env;
	// t_minishell minishell;
	t_command_line *ptr;
	char *input;

	initialize_table(data.table_op, data.table_builtins);
	initialize_operators(data.table_op);
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
		data.tokens = split_into_tokens(input);
		if (data.tokens == NULL)
			printf("Syntax error: unclosed quotes.\n");
		else
		{
			// data.tokens = handle_interpreting(&ptr, &data, &minishell);
			if (ft_strcmp(data.tokens[0], "exit") == 0)
				exit(EXIT_SUCCESS);
			if (classify_tokens(&data))
			{
				ptr = parsing(&data);
				if (ptr == NULL)
				{
					printf("Error: ptr is NULL, linked list is empty.\n");
					return (1);
				}
				printf("pipe count : %d\n", data.pipe_count);
			}
		}
	// delete me ---------------------------------------------------------v
        t_command_line *tmp = ptr;
        while (tmp)
        {
            printf("NODE : \n");
            printf("--------------\n");
            if (tmp->command)
            {
                for (int i = 0; tmp->command[i]; i++)
                    printf("  CMD[%d] : %s", i, tmp->command[i]);
            }
            else
                printf("cmd : NULL\n");
            printf("\nis_builtin : %d,\n builtin_type : %d,\n input : %s,\n output : %s,\n is_append : %d,\n heredoc : %s,\n NEXT : --->\n", tmp->is_builtin, tmp->builtin_type, tmp->input_file, tmp->output_file, tmp->append_output, tmp->heredoc_delimiter);
            // print file heredoc;
            if (tmp->heredoc_delimiter)
            {
                char* c = (char*)calloc(100, sizeof(char));
                int sz;
                int fd = open(tmp->heredoc_file, O_RDONLY);
                if (fd < 0) {
                    perror("r1");
                    exit(1);
                }
                sz = read(fd, c, 1000000);
                c[sz] = '\0';
                printf("heredoc file: %s\n", c);
            }
            printf("--------------\n");
            tmp = tmp->next;
        }

    //  Libération de la liste après l'affichage
        t_command_line *current;
        while (ptr != NULL)
        {
            current = ptr;
            ptr = ptr->next;
            free(current);
        }
    // delete me ---------------------------------------------------------^
	}
	return (0);
}
