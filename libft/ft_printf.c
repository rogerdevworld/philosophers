/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:06:47 by rmarrero          #+#    #+#             */
/*   Updated: 2025/01/24 16:39:25 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/* dejare el ft_printf para manejo de errores 
 * etc y llamar a las funciones finales */
int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		length;
	int		flag;

	i = -1;
	length = 0;
	flag = 1;
	va_start(args, str);
	while (str[++i])
	{
		if (str[i] == '%' && str[++i])
		{
			if (ft_validation(str[i]) == 1)
				is_flag(str[i], args, &length, &flag);
			else
				return (-1);
		}
		else
			ft_putchar(str[i], &length, &flag);
		if (flag == -1)
			return (-1);
	}
	return (va_end(args), length);
}
