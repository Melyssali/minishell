/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/24 16:22:30 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	skip_n_option(char **cmd, int i)
{
	while (strcmp (cmd[i], "-n") == 0)
	{
		if (cmd[i + 1] == NULL)
			return (SUCCESS);
		i++;
	}
	return (i);
}

static void	print_echo(char **cmd, int i)
{
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int	mini_echo(t_minishell *minishell)
{
	int	i;
	int	with_n;

	with_n = FALSE;
	i = 1;
	if (ft_count_args(minishell->command_line->command) == 1)
	{
		printf("\n");
		return (SUCCESS);
	}
	if (strcmp(minishell->command_line->command[i], "-n") == 0)
	{
		with_n = TRUE;
		i = skip_n_option(minishell->command_line->command, i);
		if (i == 0)
			return (SUCCESS);
	}
	print_echo(minishell->command_line->command, i);
	if (with_n == FALSE)
		printf("\n");
	return (SUCCESS);
}
