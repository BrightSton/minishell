/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:19:46 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:19:49 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = s;
	while (i < n)
	{
		temp[i] = c;
		i++;
	}
	return (s);
}
/*
#include<stdio.h>
int main ()
{
	char str[] = "BlockDMask Blog is good";
	//char* ptr = ft_strrchr(str, 'a');
	//while(ptr != '\0')
	//{
	//	printf("찾는 문자 : %c, 찾은 문자열 : %s\n", *ptr, ptr);
		//ptr = ft_strchr(ptr + 1, 'o');
	//}
	printf("처음 문자열 : %s\n", str);
	ft_memset(str,97,5);
	printf("다음 문자열 : %s\n", str);
}
*/