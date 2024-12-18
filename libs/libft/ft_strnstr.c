/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:01:32 by lscarcel          #+#    #+#             */
/*   Updated: 2024/03/21 12:52:00 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned long int	c1;
	unsigned long int	c2;

	c1 = 0;
	if (needle[0] == '\0')
		return ((char *) haystack);
	while (haystack[c1] != '\0' && c1 < len)
	{
		c2 = 0;
		while (haystack[c1 + c2] == needle[c2] && needle[c2] != '\0'
			&& (c1 + c2) < len)
		{
			c2++;
		}
		if (needle[c2] == '\0')
			return ((char *) &haystack[c1]);
		c1++;
	}
	return (0);
}
