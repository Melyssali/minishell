/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:41:18 by lscarcel          #+#    #+#             */
/*   Updated: 2023/10/26 10:33:02 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	char	*newstring;
	size_t	i;
	size_t	newlen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start > slen)
		return (ft_strdup(""));
	if (len < (slen - start))
		newlen = len;
	else
		newlen = slen - start;
	newstring = malloc(newlen + 1);
	if (newstring == NULL)
		return (NULL);
	i = 0;
	while (i < newlen)
	{
		newstring[i] = s[start + i];
		i++;
	}
	newstring[newlen] = '\0';
	return (newstring);
}
