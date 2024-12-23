/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/11/19 12:15:31 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int find_last_quote(char *s, char quote)
{
    int count_quote;
    int i;
    count_quote = 0;
    i = 0;
    while (s[i])
    {
        if (s[i] == quote)
            count_quote++;
        i++;
    }
    if (count_quote % 2 == 1)
    {
        return (ERROR);
    }
    return (1);
    // if (*s == quote)
    //  s++;
    // while (*s)
    // {
    //  if (*s == quote)
    //      return (0);
    //  s++;
    // }
    // return (ERROR);
}

int	is_space_before_quote(char *s)
{
	if (*s == DQUOTE || *s == SQUOTE)
	{
		if (*(s - 1) != SPACE && *(s - 1) != TAB && *(s - 1) != NEWLINE)
			return (ERROR);
	}
	return (0);
}
