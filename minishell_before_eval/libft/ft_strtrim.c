/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:40:24 by djang             #+#    #+#             */
/*   Updated: 2024/02/28 18:40:26 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*dest;
	unsigned int	i;
	unsigned int	j;

	if (!s1)
	{
		dest = (char *)malloc(sizeof(char));
		*dest = '\0';
		return (dest);
	}
	i = 0;
	j = ft_strlen((char *)s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > 0 && s1[j - 1] && ft_strchr(set, s1[j - 1]))
		j--;
	if (i > j)
	{
		dest = (char *)malloc(sizeof(char));
		*dest = '\0';
		return (dest);
	}
	dest = ft_substr(s1, i, j - i);
	return (dest);
}
/*
char	*ft_strtrim(char const *s1, char const *set)
{
	char			*dest;
	unsigned int	i;
	unsigned int	j;
	
	if (!s1 && !set)
		return (0);
	i = 0;
	j = ft_strlen((char *)s1);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j && s1[j - 1] && ft_strchr(set, s1[j - 1]))
		j--;
	if (i > j)
		return (ft_strdup(""));
	dest = ft_substr(s1, i, j - i);
	return (dest);
}
*/

/*
#include<stdio.h>
int main ()
{
	char str[] = "FateNo,(G)-idleFate";
	char str1[] = "Fate";
	int	str3[] = {1,2,3,4,5};
	int str4[] = {100,200,300,400};

	printf("처음 문자열 : %s\n", str);
	printf("결과 : %s\n",ft_strtrim(str, str1));

	//printf("다음 문자열 : %s\n", str);
	//char* ptr = ft_strrchr(str, 'a');
	//while(ptr != '\0')
	//{
	//	printf("찾는 문자 : %c, 찾은 문자열 : %s\n", *ptr, ptr);
		//ptr = ft_strchr(ptr + 1, 'o');
	//}
	//printf("\n");
	// printf("처음 문자열 : %d\n", str3[0]);
	// printf("다음 문자열 : %d\n", str3[1]);
	// printf("다음 문자열 : %d\n", str3[2]);
	// printf("다음 문자열 : %d\n", str3[3]);
	// printf("다음 문자열 : %d\n", str3[4]);
	// ft_memmove(str3, str4, sizeof(int) *4);
	//printf("\n");
	// printf("다음 문자열 : %d\n", str3[0]);
	// printf("다음 문자열 : %d\n", str3[1]);
	// printf("다음 문자열 : %d\n", str3[2]);
	// printf("다음 문자열 : %d\n", str3[3]);
	// printf("다음 문자열 : %d\n", str3[4]);
}
*/