/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:04:34 by lscarcel          #+#    #+#             */
/*   Updated: 2023/10/25 14:28:49 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	p;

	p = (char)c;
	i = ft_strlen(s);
	if (s == NULL)
		return (0);
	while (i >= 0)
	{
		if (s[i] == p)
			return ((char *)&s[i]);
		else
			i--;
	}
	return (0);
}
