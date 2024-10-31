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

int skip_n_option(char **cmd, int i)
{
	while (strcmp (cmd[i], "-n") == 0)
	{
		if(cmd[i + 1] == NULL)
			return(0);
		i++;
	}
	return (i);
}

void print_echo(char **cmd, int i)
{
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int echo(char **cmd)
{
	int i;
	int with_n;

	with_n = FALSE;
	i = 1;
	if(ft_count_args(cmd) == 1)
	{
		printf("\n");
		return(0);
	}
	if(strcmp (cmd[i], "-n") == 0)
	{			
		with_n = TRUE;
		i = skip_n_option(cmd, i);
		if(i == 0)
			return(0);
	}
	print_echo(cmd, i);
	if (with_n == FALSE)
		printf("\n");
	return(0);
}
