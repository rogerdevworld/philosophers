/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:43:29 by rmarrero          #+#    #+#             */
/*   Updated: 2024/11/23 13:27:02 by rmarrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_itoa_recursive(int n, char *str, int *i)
{
	if (n == -2147483648)
	{
		str[(*i)++] = '-';
		str[(*i)++] = '2';
		ft_itoa_recursive(147483648, str, i);
		return ;
	}
	if (n < 0)
	{
		str[(*i)++] = '-';
		n = -n;
	}
	if (n >= 10)
		ft_itoa_recursive(n / 10, str, i);
	str[(*i)++] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	str = (char *)malloc((ft_intlen(n) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	ft_itoa_recursive(n, str, &i);
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//itoa de chatgpt
char *itoa(int n)
{
    char *buffer;

    buffer = (char *)malloc(12 * sizeof(char));
    if (!buffer)
        return NULL;

    int index = 0;
    int isNegative = 0;

    // Manejo del caso más negativo
    if (n == -2147483648)
    {
        strcpy(buffer, "-2147483648");
        return buffer;
    }

    // Manejo de números negativos
    if (n < 0)
    {
        isNegative = 1;
        n = -n;
    }

    // Conversión a cadena
    do {
        buffer[index++] = (n % 10) + '0';
        n /= 10;
    } while (n > 0);

    if (isNegative)
        buffer[index++] = '-';

    // Invertir la cadena
    buffer[index] = '\0';
    for (int i = 0; i < index / 2; i++)
    {
        char temp = buffer[i];
        buffer[i] = buffer[index - i - 1];
        buffer[index - i - 1] = temp;
    }

    return buffer;
}

// teste con el itoa de chargpt y el ft_version
void test_itoa(int n)
{
    char *original;
    char *copy;

    original = itoa(n);
    copy = ft_itoa(n);

    printf("Número: %d\n", n);
    printf("itoa chatgpt: %s\n", original);
    printf("ft_itoa: %s\n", copy);
    if (strcmp(original, copy) == 0)
        printf("Test PASADO!\n");
    else
        printf("Test FALLIDO!\n");

    printf("\n");
    free(copy);
}

int main(void)
{
    test_itoa(0);
    test_itoa(1);
    test_itoa(123);
    test_itoa(-123);
    test_itoa(2147483647);
    test_itoa(-2147483648);
    test_itoa(10);
    test_itoa(-10);
    test_itoa(99);
    test_itoa(-99);
    test_itoa(1000);
    test_itoa(-1000);
    test_itoa(10000);
    test_itoa(-10000);
    test_itoa(123456);
    test_itoa(-123456);
    test_itoa(654321);
    test_itoa(-654321);
    test_itoa(123456789);
    test_itoa(-123456789);
    test_itoa(99999);
    test_itoa(-99999);
    test_itoa(500);
    test_itoa(-500);
    test_itoa(7500);
    test_itoa(-7500);
    test_itoa(15000);
    test_itoa(-15000);
    test_itoa(20000);
    test_itoa(-20000);
    test_itoa(30000);
    test_itoa(-30000);
    test_itoa(40000);
    test_itoa(-40000);
    test_itoa(50000);
    test_itoa(-50000);
    test_itoa(60000);
    test_itoa(-60000);
    test_itoa(70000);
    test_itoa(-70000);
    test_itoa(80000);
    test_itoa(-80000);
    test_itoa(90000);
    test_itoa(-90000);
    test_itoa(1234);
    test_itoa(-1234);
    test_itoa(5678);
    test_itoa(-5678);
    test_itoa(13579);
    test_itoa(-13579);
    test_itoa(24680);
    test_itoa(-24680);
    test_itoa(999);
    test_itoa(-999);
    test_itoa(8888);
    test_itoa(-8888);
    test_itoa(77777);
    test_itoa(-77777);
    test_itoa(222);
    test_itoa(-222);
    test_itoa(444);
    test_itoa(-444);
    test_itoa(11111);
    test_itoa(-11111);
    test_itoa(33333);
    test_itoa(-33333);
    test_itoa(55555);
    test_itoa(-55555);
    test_itoa(66666);
    test_itoa(-66666);
    test_itoa(7777);
    test_itoa(-7777);
    test_itoa(1234567);
    test_itoa(-1234567);
    test_itoa(7654321);
    test_itoa(-7654321);
    test_itoa(100000);
    test_itoa(-100000);
    test_itoa(150000);
    test_itoa(-150000);
    test_itoa(200000);
    test_itoa(-200000);
    test_itoa(250000);
    test_itoa(-250000);
    test_itoa(300000);
    test_itoa(-300000);
    test_itoa(350000);
    test_itoa(-350000);
    test_itoa(400000);
    test_itoa(-400000);
    test_itoa(450000);
    test_itoa(-450000);
    test_itoa(500000);
    test_itoa(-500000);
    test_itoa(600000);
    test_itoa(-600000);
    test_itoa(700000);
    test_itoa(-700000);
    test_itoa(800000);
    test_itoa(-800000);
    test_itoa(900000);
    test_itoa(-900000);
    test_itoa(1200000);
    test_itoa(-1200000);
    test_itoa(1500000);
    test_itoa(-1500000);
    test_itoa(1800000);
    test_itoa(-1800000);
    test_itoa(2000000);
    test_itoa(-2000000);
    test_itoa(2200000);
    test_itoa(-2200000);
    test_itoa(2500000);
    test_itoa(-2500000);
    test_itoa(2800000);
    test_itoa(-2800000);
    test_itoa(3000000);
    test_itoa(-3000000);
    test_itoa(3200000);
    test_itoa(-3200000);
    test_itoa(3500000);
    test_itoa(-3500000);
    test_itoa(3700000);
    test_itoa(-3700000);
    test_itoa(3900000);
    test_itoa(-3900000);
    test_itoa(4100000);
    test_itoa(-4100000);
    test_itoa(4300000);
    test_itoa(-4300000);
    test_itoa(4500000);
    test_itoa(-4500000);
    test_itoa(4700000);
    test_itoa(-4700000);
    test_itoa(4900000);
    test_itoa(-4900000);
    test_itoa(5100000);
    test_itoa(-5100000);
    test_itoa(5300000);
    test_itoa(-5300000);
    test_itoa(5500000);
    test_itoa(-5500000);
    test_itoa(5700000);
    test_itoa(-5700000);
    test_itoa(5900000);
    test_itoa(-5900000);
    test_itoa(6100000);
    test_itoa(-6100000);
    test_itoa(6300000);
    test_itoa(-6300000);
    test_itoa(6500000);
    test_itoa(-6500000);
    test_itoa(6700000);
    test_itoa(-6700000);
    test_itoa(6900000);
    test_itoa(-6900000);
    test_itoa(7000000);
    test_itoa(-7000000);
    test_itoa(7200000);
    test_itoa(-7200000);
    test_itoa(7400000);
    test_itoa(-7400000);
    test_itoa(7600000);
    test_itoa(-7600000);
    test_itoa(7800000);
    test_itoa(-7800000);
    test_itoa(8000000);
    test_itoa(-8000000);
    test_itoa(8200000);
    test_itoa(-8200000);
    test_itoa(8400000);
    test_itoa(-8400000);
    test_itoa(8600000);
    test_itoa(-8600000);
    test_itoa(8800000);
    test_itoa(-8800000);
    test_itoa(9000000);
    test_itoa(-9000000);
    test_itoa(9200000);
    test_itoa(-9200000);
    test_itoa(9400000);
    test_itoa(-9400000);
    test_itoa(9600000);
    test_itoa(-9600000);
    test_itoa(9800000);
    test_itoa(-9800000);
    test_itoa(10000000);
    test_itoa(-10000000);
    test_itoa(11000000);
    test_itoa(-11000000);
    test_itoa(12000000);
    test_itoa(-12000000);
    test_itoa(13000000);
    test_itoa(-13000000);
    test_itoa(14000000);
    test_itoa(-14000000);
    test_itoa(15000000);
    test_itoa(-15000000);
    test_itoa(16000000);
    test_itoa(-16000000);
    test_itoa(17000000);
    test_itoa(-17000000);
    test_itoa(18000000);
    test_itoa(-18000000);
    test_itoa(19000000);
    test_itoa(-19000000);
    test_itoa(20000000);
    test_itoa(-20000000);
    test_itoa(21000000);
    test_itoa(-21000000);
    test_itoa(22000000);
    test_itoa(-22000000);

    return 0;
}*/
