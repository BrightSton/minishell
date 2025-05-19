/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:25:26 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:25:28 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	const char	*dest;
	const char	*src;
	size_t		i;

	i = 0;
	dest = ptr1;
	src = ptr2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (dest[i] != src[i])
			return ((unsigned char)dest[i] - (unsigned char)src[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
int main()
{
	int a =ft_memcmp("t\200", "t\0", 2);
	printf("%d",a);
}
while (i < n)
	{
		if (dest[i] != src[i])
			return (dest[i] - src[i]);
		i++;
	}
	return (0);
*/