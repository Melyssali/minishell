/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:06:41 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/01 19:27:07 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptrtemp;

	if (!b)
		return (0);
	ptrtemp = (unsigned char *)b;
	while (len > 0)
	{
		*ptrtemp = (unsigned char)c;
		ptrtemp++;
		len--;
	}
	return (b);
}
