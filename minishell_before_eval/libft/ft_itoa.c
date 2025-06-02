/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:41:35 by djang             #+#    #+#             */
/*   Updated: 2024/02/28 18:41:37 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_index(int n)
{
	int	index;

	index = 1;
	if (n < 0)
	{
		index++;
		n = n * (-1);
	}
	while (n >= 10)
	{
		n = n / 10;
		index++;
	}
	return (index);
}

static void	minus_insert_num(int index, int n, char *dest)
{
	int		result;
	int		left;

	n = n * (-1);
	dest[0] = '-';
	result = n;
	left = n;
	while (index > 0)
	{
		left = result % 10;
		dest[index] = left + '0';
		result = result / 10;
		index--;
	}
}

static void	insert_num(int index, int n, char *dest)
{
	int		result;
	int		left;

	result = n;
	left = n;
	while (index >= 0)
	{
		left = result % 10;
		dest[index] = left + '0';
		result = result / 10;
		index--;
	}
}

char	*ft_itoa(int n)
{
	int		index;
	char	*dest;

	if (n == -2147483648)
	{
		dest = (char *)malloc(sizeof(char) * 12);
		ft_memmove(dest, "-2147483648", 12);
		return (dest);
	}
	index = get_index(n);
	dest = (char *)malloc(sizeof(char) * (index + 1));
	if (!dest)
		return (0);
	dest[index] = '\0';
	if (n < 0 && n > -2147483648)
		minus_insert_num(index - 1, n, dest);
	else
		insert_num(index - 1, n, dest);
	return (dest);
}

/*
static int	get_index(int n)
{
	int	index;

	index = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		index++;
	while (n != 0)
	{
		n = n / 10;
		index++;
	}
	return (index);
}

static void	minus_insert_num(int index, int n, char *dest)
{
	int		result;
	int		left;

	n = n * (-1);
	dest[0] = '-';
	result = n;
	left = n;
	while (index > 1)
	{
		index--;
		left = result % 10;
		dest[index] = left + '0';
		result = result / 10;
	}
}

static void	insert_num(int index, int n, char *dest)
{
	int		result;
	int		left;

	result = n;
	left = n;
	while (index >= 0)
	{
		index--;
		left = result % 10;
		dest[index] = left + '0';
		result = result / 10;
	}
}

char	*ft_itoa(int n)
{
	int		index;
	char	*dest;

	if (n == -2147483648)
	{
		dest = (char *)malloc(sizeof(char) * 12);
		ft_memmove(dest, "-2147483648", 12);
		return (dest);
	}
	index = get_index(n);
	dest = (char *)malloc(sizeof(char) * (index + 1));
	if (!dest)
		return (0);
	if (n < 0 && n > -2147483648)
		minus_insert_num(index, n, dest);
	else
		insert_num(index, n, dest);
	dest[index] = '\0';
	return (dest);
}
// #include <stdio.h>
// int main()
// {
// 	int size;
// 	int k = -623;
// 	//ft_itoa(-5859);
// 	printf("%s\n", ft_itoa(k));
// 	//printf ("%d",size);
// }

*/
