/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/22 10:54:30 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void free_all(t_minishell *minishell)
// {
    
// }

static int	mini_atoi(char *str, int *err)
{
	unsigned long long	ret;
	int					i;
	int					j;
	int					pn;

	i = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	pn = 1;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			pn = -1;
	j = i;
	ret = 0;
	while ('0' <= str[i] && str[i] <= '9')
		ret = ret * 10 + (str[i++] - 48);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((pn == -1 && (ret - 1) > LONG_MAX) || \
		(pn == 1 && (ret > LONG_MAX))))
		*err = 1;
	return ((int)((ret * pn) % 256));
}

int	mini_exit(t_minishell *minishell)
{
	int	ret;
	int	err;

	ret = 0;
	err = 0;
	if (minishell->command_line->command[1])
	{
		ret = almost_atoi(minishell->command_line->command[1], &err);
		if (err)
		{
			print_error("exit: ");
			print_error(minishell->command_line->command[1]);
			print_error(": numeric argument required\n");
			// free_all(minishell, NULL, 2);
		}
	}
	if (minishell->command_line->command[1] && minishell->command_line->command[1])
	{
		print_error("exit: too many arguments\n");
		minishell->data->return_value = 1;
		return ;
	}
	// if (!minishell->command_line->command[1])
	// 	free_all(minishell, NULL, minishell->data->return_value);
	// free_all(minishell, NULL, ret);
}

