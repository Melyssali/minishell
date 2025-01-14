/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/12/18 17:04:48 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*skip_space(char *s)
{
	while (*s && (*s == SPACE || *s == TAB))
		s++;
	return (s);
}

char	*iterate_word(char *s)
{
	while (*s && *s != SPACE && *s != TAB && *s != DQUOTE && *s != SQUOTE
		&& !is_operator(*s))
		s++;
	return (s);
}

char    *skip_quotes(char *s, char quote)
{
    if (*s && *s == quote)
        s++;
    return (s);
}

char	*iterate_inside_quotes(char *s, char quote)
{
	while (*s && *s != quote)
		s++;
	return (s);
}
