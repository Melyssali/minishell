/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lscarcel <lscarcel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:03:32 by lscarcel          #+#    #+#             */
/*   Updated: 2023/11/16 07:32:22 by lscarcel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

int			ft_printf(const char *format, ...);
int			ft_count_putchar(char c);
int			ft_count_putstr(char *s);
int			ft_putnbr(unsigned long nbr, char *base);
size_t		ft_strlen(const char *s);
int			ft_count_itoa(int n);
char		*ft_strdup(const char *s1);
int			ft_count_utoa(unsigned int n);
int			ft_check_identifier(char format, va_list args);
