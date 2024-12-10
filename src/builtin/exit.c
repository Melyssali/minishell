/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/07 17:15:19 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mini_exit(t_minishell *minishell)
{
	if (ft_strcmp(minishell->command_line->command[0], "exit") == 0)
	{
		if (ft_count_args(minishell->command_line->command) > 2)
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		else
			exit(0);
	}
	return (1);
}
