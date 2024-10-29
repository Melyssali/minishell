/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/23 15:15:32 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "libft.h"

// [x] gerer : echo 'this is a "test"' - affiche 1 token->  this is a "test"
// [x] gerer : echo 'this is a "test' - affiche 1 token ->  this is a "test
// [x] gerer : echo "this is a 'test" - affiche 1 token->  this is a 'test
// [x] echo"test" | grep "test ok" ne doit pas fonctionner donc 4 token et pas 5 (+ error)
// [] echo "test"123 fonctionne et affiche test123
// [] echo "test">file.txt fonctionne
// [] echo "test"&123 ne fonctionne pas

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
				s = handle_quote(s, quote);
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
