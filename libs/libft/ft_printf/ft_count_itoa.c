/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_itoa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:02:08 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/15 14:54:53 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_and_count(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_count_itoa(int n)
{
	int	count;
	int	temp_n;
	int	tens;

	count = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		count += print_and_count('-');
		n = -n;
	}
	temp_n = n;
	tens = 1;
	while (temp_n >= 10)
	{
		temp_n /= 10;
		tens *= 10;
	}
	while (tens > 0)
	{
		count += print_and_count((n / tens) % 10 + '0');
		tens /= 10;
	}
	return (count);
}
