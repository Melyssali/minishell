/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 08:48:31 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/07 08:32:46 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptrtemp;

	if (!s)
		return (0);
	ptrtemp = (char *)s;
	while (n > 0)
	{
		if (*ptrtemp == (char)c)
			return (ptrtemp);
		n--;
		ptrtemp++;
	}
	return (0);
}
