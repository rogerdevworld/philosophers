/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:23 by rmarrero          #+#    #+#             */
/*   Updated: 2025/01/24 16:33:01 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/* %char hunter */
void	is_flag(char c, va_list args, int *length, int *flag)
{
	if (c == 'c')
		ft_putchar((char)va_arg(args, int), length, flag);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), length, flag);
	else if (c == 'p')
		ft_pointer(va_arg(args, uintptr_t), length, flag);
	else if (c == 'u')
		ft_unsigned_putnbr(va_arg(args, unsigned int), length, flag);
	else if (c == 'i' || c == 'd')
		ft_putnbr(va_arg(args, int), length, flag);
	else if (c == 'x')
		ft_hex(va_arg(args, unsigned int), length, 'x', flag);
	else if (c == 'X')
		ft_hex(va_arg(args, unsigned int), length, 'X', flag);
	else if (c == '%')
		ft_putchar('%', length, flag);
}

int	ft_validation(char c)
{
	if (c == 'c' || c == 'i' || c == 's' || c == 'p'\
		|| c == 'u' || c == 'd' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (-1);
}

/* %u Print an unsigned decimal number (base 10). */
void	ft_unsigned_putnbr(unsigned int unsgined_nbr, int *length, int *flag)
{
	if (unsgined_nbr > 9)
		ft_unsigned_putnbr(unsgined_nbr / 10, length, flag);
	ft_putchar(unsgined_nbr % 10 + '0', length, flag);
}
