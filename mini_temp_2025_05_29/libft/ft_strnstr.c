/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:25:36 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:25:37 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *find, size_t len)
{
	size_t	i;
	char	*cp;
	int		c;

	i = 0;
	cp = (char *)s;
	if (!*find)
		return ((char *)s);
	if (len == 0)
		return (0);
	while (*cp && i < len)
	{
		c = 0;
		while (cp[c] && find[c] && (cp[c] == find[c]) && i + c < len)
			c++;
		if (!find[c])
			return (cp);
		cp++;
		i++;
	}
	return (0);
}

/*
#include<stdio.h>
int main()
{
    char	origin[] = "Black MaMMA";
	char	dest[] = "Ma";

    ft_strnstr(origin,dest,10);


	printf("case1 :%s\n", ft_strnstr(origin,dest,5));;
  

    return 0;
}
*/