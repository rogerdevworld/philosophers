/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 06:59:23 by rmarrero          #+#    #+#             */
/*   Updated: 2024/09/28 16:30:52 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*local_s;

	i = 0;
	local_s = (const unsigned char *)s;
	while (i < n)
	{
		if (local_s[i] == (unsigned char)c)
			return ((void *)&local_s[i]);
		i++;
	}
	return (NULL);
}
