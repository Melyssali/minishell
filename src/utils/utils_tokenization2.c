/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenization2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/18 17:46:57 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	copy_array(char *dst, char *src, size_t dstsize)
{
	char	quote;

	quote = '\0';
	if (dst == NULL || src == NULL)
		return ;
	while (*src && dstsize > 1)
	{
		if (!is_operator(*src))
		{
			if (!quote && (*src == SQUOTE || *src == DQUOTE))
				quote = *src;
		}
		if (*src != quote)
		{
			*dst = *src;
			dst++;
		}
		src++;
		dstsize--;
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
	int	length;
	int	i;

	length = 0;
	i = 0;
	while (is_operator(start_string[i]) && (start_string[i] != DQUOTE
			|| start_string[i] != SQUOTE))
	{
		i++;
		length++;
	}
	if (!length)
		length = s - start_string;
	arr[*count] = malloc(length + 1);
	if (!arr[*count])
	{
		perror("Malloc array failed.");
		free_arr_tokenization(arr);
		return ;
	}
	copy_array(arr[*count], start_string, length + 1);
	arr[*count][length] = '\0';
	(*count)++;
	arr[*count] = NULL;
}

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

void	if_not_value(char **value, t_data *data, int y, int x)
{
	if (!*value)
	{
		if (data->tokens[y][x] == '?')
			*value = ft_itoa(data->return_value);
		else
			*value = "";
	}
}
