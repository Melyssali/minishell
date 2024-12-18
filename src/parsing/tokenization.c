/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/18 17:09:54 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// this file tokenize an input into array
#include "../../include/minishell.h"

static char	*handle_string(char *s)
{
	s = skip_space(s);
	s = iterate_word(s);
	if (*s && (*s == SPACE || *s == TAB || *s == NEWLINE) && *(s + 1) != '\0')
		s = skip_space(s);
	else if (*s && (*s == DQUOTE || *s == SQUOTE) && *(s + 1) != '\0')
	{
		if (find_last_quote(s, *s) == ERROR)
			return (NULL);
		else
		{
			s = handle_quote(s, *s);
			if (s == NULL)
			{
				printf("Need space before first quote\n");
				return (NULL);
			}
		}
	}
	else if (is_operator(*s))
	{
		while (is_operator(*s))
			s++;
	}
	return (s);
}

static int	count_tokens(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		s = handle_string(s);
		if (!s)
			return (ERROR);
		count++;
	}
	return (count);
}

static char	**fill_arr(char **arr, char *s, int how_many_tokens, t_data *data)
{
	int		count;
	char	*start_string;

	count = 0;
	while (count < how_many_tokens)
	{
		s = skip_space(s);
		start_string = s;
		s = iterate_word(s);
		if (*s == DQUOTE || *s == SQUOTE)
		{
			if (data->is_double_quotes && *s == SQUOTE)
				data->is_double_quotes = 0;
			s = handle_quote(s, *s);
		}
		while (is_operator(*s))
			s++;
		handle_arr(s, arr, &count, start_string);
	}
	return (arr);
}

char	**split_into_tokens(char *s, t_data *data)
{
	char	**arr;
	int		how_many_tokens;

	if (!s)
		return (NULL);
	how_many_tokens = count_tokens(s);
	if (how_many_tokens == ERROR)
	{
		return (NULL);
	}
	arr = NULL;
	arr = malloc(sizeof(char *) * (how_many_tokens + 1));
	if (!arr)
	{
		perror("Malloc failed. ");
		exit(EXIT_FAILURE);
	}
	return (fill_arr(arr, s, how_many_tokens, data));
}
