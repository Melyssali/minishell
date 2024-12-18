/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:31:52 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/16 07:35:51 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_base_check(char *base)
{
	int	baselength;
	int	i;
	int	j;

	i = 0;
	baselength = ft_strlen(base);
	if (baselength < 2)
		return (0);
	while (i < baselength)
	{
		j = i + 1;
		if (base[i] == '+' || base[i] == '-' || base[i] == ' ')
			return (0);
		while (j < baselength)
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	ft_print_nbr(unsigned long nLong, int Basevalue, char *symbols)
{
	int	count;

	count = 0;
	if (nLong >= (unsigned long)Basevalue)
	{
		count += ft_print_nbr(nLong / Basevalue, Basevalue, symbols);
		count += ft_count_putchar(symbols[nLong % Basevalue]);
	}
	else
	{
		count += ft_count_putchar(symbols[nLong]);
	}
	return (count);
}

int	ft_putnbr(unsigned long nbr, char *base)
{
	int	base_length;
	int	count;

	count = 0;
	if (!ft_base_check(base))
		return (0);
	base_length = ft_strlen(base);
	count += ft_print_nbr(nbr, base_length, base);
	return (count);
}
