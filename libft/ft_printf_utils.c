/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:07:36 by rmarrero          #+#    #+#             */
/*   Updated: 2025/01/24 16:27:51 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/* %c Prints a single character. */
void	ft_putchar(char character, int *length, int *flag)
{
	if (write(1, &character, 1) == -1)
	{
		(*flag) = -1;
		return ;
	}
	(*length)++;
}

/* %s Prints a string (as defined by default in C) */
void	ft_putstr(char *args, int *length, int *flag)
{
	size_t	i;

	i = 0;
	if (!args)
	{
		if (write(1, "(null)", 6) == -1)
			(*flag) = -1;
		(*length) += 6;
		return ;
	}
	while (args[i])
	{
		ft_putchar(args[i], length, flag);
		i++;
	}
}

/* 
- %d Prints a decimal number (base 10).
- %i Prints an integer in base 10.
*/
void	ft_putnbr(int nbr, int *length, int *flag)
{
	if (nbr == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			(*flag) = -1;
		(*length) += 11;
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar('-', length, flag);
		ft_putnbr(nbr * -1, length, flag);
	}
	else
	{
		if (nbr > 9)
			ft_putnbr(nbr / 10, length, flag);
		ft_putchar(nbr % 10 + '0', length, flag);
	}
}

/* %p The void pointer * given as argument is printed in hexadecimal format. */
void	ft_pointer(uintptr_t pointer, int *length, int *flag)
{
	char	str_hex[17];
	int		i;
	char	*hex;

	hex = "0123456789abcdef";
	i = 0;
	if (pointer == 0)
	{
		if (write(1, "(nil)", 5) == -1)
			(*flag) = -1;
		(*length) += 5;
		return ;
	}
	if (write(1, "0x", 2) == -1)
		return ((*flag) = -1, (void)0);
	(*length) += 2;
	while (pointer != 0)
	{
		str_hex[i++] = hex[pointer % 16];
		pointer = pointer / 16;
	}
	while (i--)
		ft_putchar(str_hex[i], length, flag);
}

/* %x Prints a hexadecimal number (base 16) in lower case.
%X Prints a hexadecimal number (base 16) in uppercase. */
void	ft_hex(unsigned int nbr, int *length, char x, int *flag)
{
	char	str_hex[17];
	char	*hex;
	int		i;

	if (x == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	i = 0;
	if (nbr == 0)
	{
		ft_putchar('0', length, flag);
		return ;
	}
	while (nbr != 0)
	{
		str_hex[i] = hex[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	while (i--)
		ft_putchar(str_hex[i], length, flag);
}
