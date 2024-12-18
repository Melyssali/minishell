/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 07:27:55 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/15 15:13:26 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_identifier(char format, va_list args)
{
	if (format == '%')
		return (ft_count_putchar('%'));
	else if (format == 'c')
		return (ft_count_putchar((char)va_arg(args, int)));
	else if (format == 's')
		return (ft_count_putstr(va_arg(args, char *)));
	else if (format == 'd' || format == 'i')
		return (ft_count_itoa(va_arg(args, int)));
	else if (format == 'u')
		return (ft_count_utoa(va_arg(args, unsigned int)));
	else if (format == 'p')
	{
		ft_count_putstr("0x");
		return (2 + ft_putnbr(va_arg(args, unsigned long), "0123456789abcdef"));
	}
	else if (format == 'x' || format == 'X')
	{
		if (format == 'x')
			return (ft_putnbr(va_arg(args, unsigned int), "0123456789abcdef"));
		else
			return (ft_putnbr(va_arg(args, unsigned int), "0123456789ABCDEF"));
	}
	return (0);
}
