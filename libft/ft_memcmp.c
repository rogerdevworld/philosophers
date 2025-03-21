/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 04:41:55 by rmarrero          #+#    #+#             */
/*   Updated: 2024/09/28 16:30:15 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*local_s1;
	const unsigned char	*local_s2;

	i = 0;
	local_s1 = (const unsigned char *)s1;
	local_s2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (local_s1[i] != local_s2[i])
			return (local_s1[i] - local_s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char s1[]= "\0";
	char s2[]= "";
	printf("ft_ : %i\n", ft_memcmp(s1, s2, 6));
	printf("original: %i\n", memcmp(s1, s2, 6));
	return 0;
}*/
