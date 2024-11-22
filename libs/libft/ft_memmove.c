/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:03:11 by lscarcel          #+#    #+#             */
/*   Updated: 2023/10/25 13:00:18 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;

	ptrsrc = (unsigned char *)src;
	ptrdst = (unsigned char *)dst;
	if (dst == NULL || src == NULL)
		return (0);
	if (ptrsrc < ptrdst && ptrsrc + len >= ptrdst)
	{
		while (len > 0)
		{
			ptrdst[len - 1] = ptrsrc[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
