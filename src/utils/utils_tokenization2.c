/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenization2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/23 15:16:57 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"


// echo"test" will not work, shell makes one token 
// who is echo"test", and its not a working command

char	*handle_quote(char *s, char quote)
{
	if (is_space_before_quote(s) == ERROR)
	{
		while (*s && *s != SPACE && *s != TAB && *s != NEWLINE)
			s++;
	}
	else
	{
			s = skip_quotes(s, quote);
			s = iterate_inside_quotes(s, quote);
			s = skip_quotes(s, quote);
	}
	return (s);
}

void	handle_arr(char *s, char **arr, int *count, char *start_string)
{
	arr[*count] = malloc(s - start_string + 1);
	if (!arr[*count])
	{
		perror("Malloc array failed.");
		free_arr_tokenization(arr);
		return ;
	}
	ft_strlcpy(arr[*count], start_string, s - start_string + 1);
	arr[*count][s - start_string] = '\0';
	(*count)++;
	arr[*count] = NULL;
}

void	free_arr_tokenization(char **arr)
{
	int	y;

	y = 0;
	while (arr[y] != NULL)
	{
		free(arr[y]);
		y++;
	}
	free(arr);
}