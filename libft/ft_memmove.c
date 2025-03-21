/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 06:48:32 by rmarrero          #+#    #+#             */
/*   Updated: 2024/09/27 13:42:57 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*local_dest;
	const unsigned char	*local_src;

	if (!dest || !src)
		return (NULL);
	local_dest = (unsigned char *)dest;
	local_src = (const unsigned char *)src;
	if (local_dest < local_src)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
			local_dest[n] = local_src[n];
	}
	return (dest);
}
