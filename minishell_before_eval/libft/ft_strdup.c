/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:59:50 by djang             #+#    #+#             */
/*   Updated: 2024/02/28 15:59:52 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		len;
	char	*temp;

	len = 0;
	while (str[len])
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	temp = dest;
	while (*str)
	{
		*dest = *str;
		dest++;
		str++;
	}
	*dest = '\0';
	return (temp);
}

/*
#include<stdio.h>
int	main ()
{
	char *s;
	char *a;
	s = "qwerat";
	*a = 0;
	ft_strdup(a);
	printf("%s\n", ft_strdup(a));
	printf("%s\n", ft_strdup(s));
	return 0;
}
*/