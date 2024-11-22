/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_utoa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:02:08 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/15 14:55:22 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_count_utoa(unsigned int n)
{
	char			str[11];
	int				len;
	unsigned int	temp_n;
	int				j;

	len = 0;
	if (n == 0)
		return (write(1, "0", 1));
	temp_n = n;
	while (temp_n != 0)
	{
		len++;
		temp_n /= 10;
	}
	str[len] = '\0';
	j = len - 1;
	while (n > 0)
	{
		str[j--] = (n % 10) + '0';
		n /= 10;
	}
	return (write(1, str, len));
}
