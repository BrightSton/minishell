/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:25:11 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:25:13 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*temp;
	size_t		i;

	temp = s;
	i = 0;
	while (i < n)
	{
		if (temp[i] == c)
			return ((void *)temp + i);
		i++;
	}
	return (0);
}
