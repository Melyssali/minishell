/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 07:44:50 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/01 17:21:10 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

static void	ft_free_table(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

static int	count_words(const char *s, char c)
{
	int	sep_count;
	int	start;

	sep_count = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] == c)
			start++;
		if (s[start])
		{
			sep_count++;
			while (s[start] != c && s[start])
				start++;
		}
	}
	return (sep_count);
}

static char	*ft_allocate_and_copy_substring(char const *s, int start, int end)
{
	char	*substring;

	substring = malloc(sizeof(char) * (end - start + 1));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, &s[start], end - start + 1);
	return (substring);
}

static char	*find_and_copy_next_word(const char *s, char c, int *start)
{
	int	end;
	int	temp_start;

	temp_start = *start;
	while (s[temp_start] == c)
		temp_start++;
	end = temp_start;
	while (s[end] != c && s[end])
		end++;
	*start = end;
	return (ft_allocate_and_copy_substring(s, temp_start, end));
}

char	**ft_split(char const *s, char c)
{
	int		table_id;
	int		start;
	char	**table;
	int		sep_count;

	table_id = 0;
	start = 0;
	sep_count = count_words(s, c);
	table = malloc(sizeof(char *) * (sep_count + 1));
	if (!table)
		return (NULL);
	while (s[start] && table_id < sep_count)
	{
		table[table_id] = find_and_copy_next_word(s, c, &start);
		if (!table[table_id])
		{
			ft_free_table(table);
			return (NULL);
		}
		table_id++;
	}
	table[table_id] = NULL;
	return (table);
}
