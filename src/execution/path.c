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

static char	*cmd_not_found(char *cmd)
{
    write(2, "minishell : ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": No such file or directory\n", 21);
	return (NULL);
}

int	build_cmd(t_minishell *minishell)
{
	char	**path_tab;
	char	*cmd_path;
	int		i;

	path_tab = ft_split(minishell->envp, ':');
	i = 0;
	while (path_tab && path_tab[i])
	{
		path_tab[i] = ft_strjoin(path_tab[i], "/");
		cmd_path = ft_strjoin_no_free(path_tab[i], minishell->cmd_tab[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			free_tab(path_tab);
			minishell->command_line->cmd_path = cmd_path;
			return (SUCCESS);
		}
		free(cmd_path);
		i++;
	}
	free_tab(path_tab);
	cmd_not_found(minishell->command_line->command[0]);
    return (FAIL);
}

