/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:06:56 by rmarrero          #+#    #+#             */
/*   Updated: 2024/09/26 12:35:50 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
//#include <stdio.h>
//#include <stdlib.h>

/*
void    ft_bzero(void *s, size_t n);
size_t  ft_strlen(const char *str);
char    *ft_strdup(const char *s1);
void    *ft_calloc(size_t count, size_t size);
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*pointer;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	pointer = ft_calloc(len + 1, sizeof(char));
	if (!pointer)
		return (NULL);
	i = 0;
	while (i < len)
	{
		pointer[i] = s[start + i];
		i++;
	}
	return (pointer);
}
/*
int	main(void)
{
	char s[] = "Hi new world, new testing text for this function.";
	printf("new testing: %s\n", ft_substr(s, 14, 11));
	return (0);
}

void    ft_bzero(void *s, size_t n)
{
        size_t                  i;
        unsigned char   *str;

        str = (unsigned char *)s;
        i = 0;
        while (i < n)
        {
                str[i] = '\0';
                i++;
        }
}

size_t  ft_strlen(const char *str)
{
        int     length;

        length = 0;
        while (str[length])
                length++;
        return (length);
}
char    *ft_strdup(const char *s1)
{
        size_t  i;
        char    *duplicado;

        i = 0;
        duplicado = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
        if (!duplicado)
                return (NULL);
        while (s1[i])
        {
                duplicado[i] = s1[i];
                i++;
        }
        duplicado[i] = '\0';
        return (duplicado);
}

void    *ft_calloc(size_t count, size_t size)
{
        size_t                  i;
        unsigned char   *pointer;

        i = 0;
        pointer = malloc(count * size);
        if (!pointer)
                return (NULL);
        ft_bzero(pointer, count * size);
        return (pointer);
}
*/
