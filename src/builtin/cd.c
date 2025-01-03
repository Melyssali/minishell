/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/24 14:40:36 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	mini_cd(t_minishell *minishell)
{
	char	cwd[10000];

	if (ft_count_args(minishell->command_line->command) > 2)
	{
		print_error("minishell: cd: too many arguments\n");
		return (FAIL);
	}
	else if (ft_count_args(minishell->command_line->command) == 1)
	{
		print_error("minishell: cd: only with one relative or absolute path\n");
		return (FAIL);
	}
	else if (chdir(minishell->command_line->command[1]) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			update_env_value("PWD", cwd, minishell);
			return (SUCCESS);
		}
		return (FAIL);
	}
	print_error("minishell: cd: ");
	print_error(minishell->command_line->command[1]);
	print_error(": No such file or directory\n");
	return (FAIL);
}
