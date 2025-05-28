/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:39:52 by djang             #+#    #+#             */
/*   Updated: 2024/02/28 18:39:54 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*temp;
	size_t		i;

	i = 0;
	if (start >= ft_strlen((char *)s))
		len = 0;
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	while (i < len)
	{
		temp[i] = s[start];
		i++;
		start++;
	}
	temp[i] = '\0';
	return (temp);
}

/*
	if (start >= ft_strlen((char *)s))
		return ((char *)s+start);
*/