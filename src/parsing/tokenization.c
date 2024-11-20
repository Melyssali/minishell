/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/19 16:43:48 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// this file tokenize an input into array
#include "../../include/minishell.h"
// delete me ---------------------------------------------------------
// [] echo "test"123 fonctionne et affiche test123
// delete me ---------------------------------------------------------

char	**split_into_tokens(char *s);
static int	count_tokens(char *s);
static char	**fill_arr(char **arr, char *s, int how_many_tokens);

static int	count_tokens(char *s)
{
	int	count;
	char	quote;

	count = 0;
	while (*s)
	{
		s = skip_space(s);
		s = iterate_word(s);
		if (*s && (*s == SPACE || *s == TAB || *s == NEWLINE) && *(s + 1) != '\0')
			s = skip_space(s);
		else if (*s && (*s == DQUOTE || *s == SQUOTE) && *(s + 1) != '\0')
		{
			quote = *s;
			if (find_last_quote(s, quote) == ERROR)
				return (ERROR);
			else
			{
				s = handle_quote(s, quote);
				if (s == NULL)
				{
					printf("Need space before first quote\n");
					return (ERROR);
				}
			}
		}
		count++;
	}
	return (count);
}

static char	**fill_arr(char **arr, char *s, int how_many_tokens)
{
	int	count;
	char *start_string;
	char	quote;

	count = 0;
	while (count < how_many_tokens)
	{
		s = skip_space(s);
		start_string = s;
		s = iterate_word(s);
		if (*s == DQUOTE || *s == SQUOTE)
		{
			quote = *s;
			s = handle_quote(s, quote);
		}
		handle_arr(s, arr, &count, start_string);
	}	
	return (arr);
}

char	**split_into_tokens(char *s)
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
	return (fill_arr(arr, s, how_many_tokens));
}
