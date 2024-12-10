/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenization2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/08 22:52:39 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// echo"test" will not work, shell makes one token
// who is echo"test", and its not a working command


static void	copy_array(char *dst, const char *src)
{
	char	quote;

	quote = '\0';
	if (dst == NULL || src == NULL)
		return ;
	while (*src)
	{
		if (!quote && (*src == SQUOTE || *src == DQUOTE))
			quote = *src;	
		if (*src != quote)
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
}

char	*handle_quote(char *s, char quote)
{
		s = skip_quotes(s, quote);
		s = iterate_inside_quotes(s, quote);
		s = skip_quotes(s, quote);
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
	copy_array(arr[*count], start_string);
	arr[*count][s - start_string] = '\0';
	(*count)++;
	arr[*count] = NULL;
}
