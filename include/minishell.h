/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/24 14:39:38 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../libs/libft/libft.h"
#include <readline/readline.h>


typedef struct s_minishell {
	char **env;
	char **envp;
}	t_minishell;


// -- BUILTINS -- //
int     mini_cd(char **cmd, t_minishell *minishell);
void cd_error(char **cmd);
int ft_env(t_minishell *minishell);
int ft_count_args(char **cmd);
char	*ft_getenv(char *var, t_minishell *minishell);
int update_env_var(char *key, char *value, t_minishell *minishell);
void copy_env(t_minishell *minishell, char **envp);


#endif