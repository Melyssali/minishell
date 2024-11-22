/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 08:36:46 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/16 08:44:39 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_check_identifier(format[i], args);
		}
		else
		{
			count += ft_count_putchar(format[i]);
		}
		i++;
	}
	va_end(args);
	return (count);
}

	// #include <stdio.h>
	// #include <limits.h>
	// int main(void)
	// {
// 		// unsigned int nbr = 3735928559;
// 		 // int num = 42;
		// int ret1;
		// int ret2;
		// printf("----------test pour %%c----------\n");
		// ret1 = printf("%% %% %% %c\n", '0');
		// ret2 = ft_printf("%c\n", '0');
		// printf("compteur de printf : %d\n", ret1);
		// ft_printf("compteur de ft_printf : %d\n", ret2);
		// printf("\n");
// 		// printf("----------test pour %%s----------\n");
// 		// ret1 = printf("%s\n", "une belle String");
// 		 // ret2 = ft_printf("%s\n", "une belle String");
// 		 // printf("compteur de printf : %d\n", ret1);
//     	// ft_printf("compteur de ft_printf : %d\n", ret2);
// 		// printf("\n");
// 		// printf("----------test pour %%d----------\n");
// 		// ret1 = printf("%d\n", 45);
// 		// ret2 = ft_printf("%d\n", 45);
// 		// printf("compteur de printf : %d\n", ret1);
// 		// ft_printf("compteur de ft_printf : %d\n", ret2);
// 		// printf("\n");
// 		// printf("----------test pour %%i----------\n");
// 		// ret1 = printf("%i\n", 9);
// 		// ret2 = ft_printf("%i\n", 9);
// 		// printf("compteur de printf : %i\n", ret1);
// 		// ft_printf("compteur de ft_printf : %i\n", ret2);
		// printf("\n");
// 		// printf("----------test pour %%u----------\n");
// 		// ret1 = printf("%u\n", UINT_MAX);
// 		// ret2 = ft_printf("%u\n", UINT_MAX);
// 		// printf("compteur de printf : %u\n", ret1);
// 		// ft_printf("compteur de ft_printf : %u\n", ret2);
// 		// printf("\n");
// 		// printf("----------test pour %%p----------\n");
// 		// ret1 = printf("%p\n", (void*)&num);
// 		// ret2 = ft_printf("%p\n", (void*)&num);
// 		// printf("compteur de printf : %d\n", ret1);
// 		// ft_printf("compteur de ft_printf : %d\n", ret1);
// 		// printf("\n");
// 		// printf("----------test pour %%x----------\n");
// 		// ret1 = printf("%X\n %X\n %lX\n %lX\n %lX\n %X\n %X\n", INT_MAX,
//				INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
// 		// printf("\n");
// 		// ret2 = ft_printf("%X\n %X\n %X\n %X\n %X\n %X\n %X\n", INT_MAX,
//				INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
// 		// printf("\n");
// 		// printf("compteur de printf : %d\n", ret1);
// 		// ft_printf("compteur de ft_printf : %d\n", ret2);
// 		// printf("\n");

// 		// printf("----------test pour %%x----------\n");
// 		// ret1 = printf("%X\n %X\n", 0, -42);
// 		// ret2 = ft_printf("%X\n %X\n", 0, -42);
// 		// printf("compteur de printf : %d\n", ret1);
// 		// ft_printf("compteur de ft_printf : %d\n", ret2);
// 		// printf("\n");
// 		// printf("----------test pour %%X----------\n");
// 		// ret1 = printf("%X\n", nbr);
// 		// ret2 = ft_printf("%X\n", nbr);
// 		// printf("compteur de printf : %d\n", ret1);
// 		// ft_printf("compteur de ft_printf : %d\n", ret2);
// 		// printf("\n");

// 		printf("(%d)", printf("%lX", LONG_MAX));
// 		printf("\n");
// 		ft_printf("(%d)", ft_printf("%X", LONG_MAX));
// 		printf("\n");
// }
