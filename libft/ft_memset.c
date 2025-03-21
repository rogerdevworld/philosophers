/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:22:10 by rmarrero          #+#    #+#             */
/*   Updated: 2024/09/17 00:02:32 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*local_s;

	local_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		local_s[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int 	main(void)
{
	char str[] = "hola";
	printf("antes: %s\n", str);
	ft_memset(str, 1, 2);
	printf("despues: %s\n", str);
}
*/		
