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

void skip_and_free(t_minishell *minishell)
{
	t_command_line *tmp;

	tmp = minishell->command_line;

	minishell->command_line = minishell->command_line->next;
	if (tmp->input_file)
		free(tmp->input_file);
	if (tmp->output_file)
		free(tmp->output_file);
	free(tmp);
}

char **lst_to_arr(t_env_var *env)
{
    t_env_var *lst;
    char **dest;
    int i;
    int len;

    len = len_list(env);
    dest = (char **)malloc(sizeof(char *) * (len + 1));
    if (!dest)
        return (NULL);

    lst = env;
    i = 0;
    while (lst != NULL)
    {
        dest[i] = ft_strjoin_no_free(lst->key, "=");
        char *full_str = ft_strjoin_no_free(dest[i], lst->value);
        free(dest[i]);
        dest[i] = full_str;
        lst = lst->next;
        i++;
    }
    dest[i] = NULL;
    return (dest);
}


int len_list(t_env_var *env)
{
    int len = 0;
    t_env_var *tmp = env;

    while (tmp != NULL)
    {
        len++;
        tmp = tmp->next;
    }
    return len;
}

void	init_struct(t_minishell *minishell, char **envp)
{
	minishell->envp = envp;
	copy_env(minishell);
	minishell->data = malloc(sizeof(t_data));
	if (!minishell->data)
	{
    	perror("malloc failed");
    	exit(EXIT_FAILURE);
	}
}

int	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (TRUE);
}