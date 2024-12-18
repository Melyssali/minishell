/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_no_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:38:05 by lscarcel          #+#    #+#             */
/*   Updated: 2024/07/24 14:37:10 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_no_free(char *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*newstring;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstring = malloc((s1len + s2len) + 1);
	ft_strlcpy(newstring, s1, s1len + 1);
	ft_strlcat(newstring, s2, s1len + s2len + 1);
	return (newstring);
}
