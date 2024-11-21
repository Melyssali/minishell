/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_interpreting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/20 21:38:29 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"
    
//  voir si lolo gere le fait que la variable tapée est valide ou non
// Une variable doit obligatoirement commencer par lettre ou underscore mais pas par un chiffre

char	**handle_interpreting(t_env_var *ptr, t_data *data, t_minishell *minishell)
{
	int	y;
	int x;
	char *value;
	char *temp;
	int	size;

	y = 0;
	while (data->tokens[y])
	{
		x = 0;
		while (data->tokens[y][x])
		{
			if (data->tokens[y][x] == DOLLAR)
			{
				while (data->tokens[y][x] == DOLLAR)
					x++;
				if (ft_isalpha(data->tokens[y][x]) || data->tokens[y][x] == '_')
				{
					size = count_variable(&data->tokens[y][x]);
					temp = copy_variable(&data->tokens[y][x], size);
					value = ft_getenv(temp, minishell);
					free(temp);
					if (!value)
						value = "";
					data->tokens[y] = copy_value(data->tokens[y], &data->tokens[y][x], value, size);
				}
			}
			x++;
		}
		y++;
	}
	return (data->tokens);
}

int	count_variable(char *s)
{
	int	count;

	count = 0;
	while (s[count] && (ft_isalnum(s[count]) || s[count] == '_'))
        count++;
	return (count);
}

char	*copy_variable(char *s, int size)
{
	char *temp;
	int i;

	i = 0;
	temp = malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	while (i < size)
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char *copy_value(char *token, char *start, char *value, int size)
{
    int len_before;
    int len_value;
    int len_after;
    int total_size;
    char *new_token;

	len_before = start - token;
	len_value = ft_strlen(value);
	len_after = ft_strlen(start + size);
	total_size = len_before + len_value + len_after;
	new_token = malloc(sizeof(char) * (total_size + 1));
    if (!new_token)
        return NULL;
    ft_memcpy(new_token, token, len_before);
    ft_memcpy(new_token + len_before, value, len_value);
    ft_memcpy(new_token + len_before + len_value, start + size, len_after);
    new_token[total_size - 1] = '\0';
    free(token);
    return (new_token);
}
