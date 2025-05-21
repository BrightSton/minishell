/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:24:57 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:24:58 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] == s2[i])
			i++;
		else if (s1[i] > s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else if (s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;

	while ((s1[i] || s2[i]) && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/*
#include<stdio.h>
int main()
{
	char *s1;
	char *s2;
	int i = 5;
	s1 ="abcde";
	s2 ="abcde" ;

	printf("%d\n",ft_strncmp(s1,s2,8));
	printf("%d\n",ft_strncmp("test\200", "test\0", 6))
	
}
*/