/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:46:22 by rmarrero          #+#    #+#             */
/*   Updated: 2024/09/13 12:59:38 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*duplicado;

	if (s1 == NULL)
		return (NULL);
	duplicado = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!duplicado)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		duplicado[i] = s1[i];
		i++;
	}
	duplicado[i] = '\0';
	return (duplicado);
}
