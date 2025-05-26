/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:20:32 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:20:33 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*temp;
	const char		*s;
	size_t			i;

	if (n == 0 || dest == src)
		return (dest);
	if (dest == NULL && src == NULL)
		return (NULL);
	temp = dest;
	s = src;
	i = 0;
	while (i < n)
	{
		temp[i] = s[i];
		i++;
	}
	return (dest);
}

/*
#include<stdio.h>
int main ()
{
	char str[] = "BlackMama";
	char str1[] = "No,(G)-idle";
	int	str3[] = {1,2,3,4,5};
	int str4[] = {100,200,300,400};
	//char* ptr = ft_strrchr(str, 'a');
	//while(ptr != '\0')
	//{
	//	printf("찾는 문자 : %c, 찾은 문자열 : %s\n", *ptr, ptr);
		//ptr = ft_strchr(ptr + 1, 'o');
	//}
	printf("처음 문자열 : %s\n", str);
	// printf("다음 문자열 : %d\n", str3[1]);
	// printf("다음 문자열 : %d\n", str3[2]);
	// printf("다음 문자열 : %d\n", str3[3]);
	// printf("다음 문자열 : %d\n", str3[4]);
	ft_memcpy(str, str1, 12);
	printf("\n");
	printf("다음 문자열 : %s\n", str);
	// printf("다음 문자열 : %d\n", str3[1]);
	// printf("다음 문자열 : %d\n", str3[2]);
	// printf("다음 문자열 : %d\n", str3[3]);
	// printf("다음 문자열 : %d\n", str3[4]);
}
*/