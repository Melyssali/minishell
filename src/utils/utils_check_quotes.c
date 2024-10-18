/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melyssa <melyssa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:44:13 by mlesein           #+#    #+#             */
/*   Updated: 2024/10/17 21:04:53 by melyssa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	find_last_quote(char *s, char quote)
{
		while (*s)
		{
			if (*s == quote)
				return (0);
			s++;
		}
	return (ERROR);
}

int	is_space_before_quote(char *s)
{
	if (*s == '\"' || *s == '\'')
	{
		if (*(s - 1) != ' ' && *(s - 1) != '\t' && *(s - 1) != '\n')
			return (ERROR);
	}
	return (0);
}