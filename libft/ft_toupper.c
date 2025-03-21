/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 08:12:23 by rmarrero          #+#    #+#             */
/*   Updated: 2024/09/18 06:32:54 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
	return (c);
}
/*
int main(void)
{
	char	str[] = "hola";
	int 	i = 0;
	while (str[i])
	{
		printf("%c", ft_toupper(str[i]));
		i++;
	}
}*/
