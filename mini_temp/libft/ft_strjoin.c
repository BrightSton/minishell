/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:07 by djang             #+#    #+#             */
/*   Updated: 2024/02/28 18:40:09 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*temp;

	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	temp = (char *)malloc(sizeof(char) * (i + j + 1));
	if (!temp)
		return (0);
	ft_memcpy(temp, s1, i);
	ft_memcpy(temp + i, s2, j);
	temp[i + j] = '\0';
	return (temp);
}

/*
#include<stdio.h>
int main ()
{
	char str[] = "BlackMama";
	char str1[] = "No,(G)-idle";
	int	str3[] = {1,2,3,4,5};
	int str4[] = {100,200,300,400};

	printf("처음 문자열 : %s\n", str);
	printf("처음 문자열 : %s\n", str1);
	printf("%s\n",ft_strjoin(str, str1));

	//printf("다음 문자열 : %s\n", str);
	//char* ptr = ft_strrchr(str, 'a');
	//while(ptr != '\0')
	//{
	//	printf("찾는 문자 : %c, 찾은 문자열 : %s\n", *ptr, ptr);
		//ptr = ft_strchr(ptr + 1, 'o');
	//}
	printf("\n");
	// printf("처음 문자열 : %d\n", str3[0]);
	// printf("다음 문자열 : %d\n", str3[1]);
	// printf("다음 문자열 : %d\n", str3[2]);
	// printf("다음 문자열 : %d\n", str3[3]);
	// printf("다음 문자열 : %d\n", str3[4]);
	// ft_memmove(str3, str4, sizeof(int) *4);
	printf("\n");
	// printf("다음 문자열 : %d\n", str3[0]);
	// printf("다음 문자열 : %d\n", str3[1]);
	// printf("다음 문자열 : %d\n", str3[2]);
	// printf("다음 문자열 : %d\n", str3[3]);
	// printf("다음 문자열 : %d\n", str3[4]);
}
*/