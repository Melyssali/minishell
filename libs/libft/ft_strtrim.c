/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:15:05 by lscarcel          #+#    #+#             */
/*   Updated: 2023/10/26 14:18:13 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(char const *s, char const *set)
{
	int	start;

	start = 0;
	while (s[start] != '\0' && ft_strchr(set, s[start]) != NULL)
		start++;
	return (start);
}

static int	find_end(char const *s, char const *set, int len)
{
	int	end;

	end = len - 1;
	while (end >= 0 && ft_strchr(set, s[end]) != NULL)
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	size_t	size;
	char	*new_str;

	if (s1 == NULL)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set, ft_strlen(s1));
	if (start > end)
	{
		new_str = malloc(1);
		if (new_str == NULL)
			return (NULL);
		new_str[0] = '\0';
		return (new_str);
	}
	size = end - start + 1;
	new_str = malloc(size + 1);
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, &s1[start], size + 1);
	return (new_str);
}
