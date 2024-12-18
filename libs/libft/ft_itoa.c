/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:29:55 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/01 17:20:16 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int	i;
	int	temp_n;

	i = 1;
	temp_n = n;
	if (temp_n < 0)
	{
		temp_n = temp_n * (-1);
		i++;
	}
	while (temp_n / 10 != 0)
	{
		temp_n = temp_n / 10;
		i++;
	}
	return (i);
}

static void	fill_string(char *str, int n, int len)
{
	int	j;

	j = len - 1;
	if (n == 0)
	{
		str[0] = '0';
		return ;
	}
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[j] = (n % 10) + '0';
		n = n / 10;
		j--;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*new_string;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_count(n);
	new_string = malloc(len + 1);
	if (new_string == NULL)
		return (NULL);
	new_string[len] = '\0';
	fill_string(new_string, n, len);
	return (new_string);
}
