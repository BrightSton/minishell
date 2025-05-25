/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:21:32 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:21:34 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*s;

	if ((!dest || !src) && !n)
		return (0);
	s = (char *)src;
	i = ft_strlen(dest);
	j = ft_strlen((char *)src);
	k = 0;
	if (i >= n)
		return (j + n);
	while (i + k + 1 < n && src[k])
	{
		dest[i + k] = src[k];
		k++;
	}
	dest[i + k] = '\0';
	return (i + j);
}

/*
size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if ((!dest || !src) && !n)
		return (0);
	while (dest[i])
		i++;
	while (src[j])
		j++;
	if (i >= n)
		return (j + n);
	while (i + k + 1 < n && src[k])
	{
		dest[i + k] = src[k];
		k++;
	}
	dest[i + k] = '\0';
	return (i + j);
}
*/
/*
size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	if((!dest || !src) && !n)
		return (0);
	if (n == 0)
		return (0);
	while (dest[i])
		i++;
	while (src[j])
		j++;
	while (i + k + 1 < n && src[k])
	{
		dest[i + k] = src[k];
		k++;
	}
	dest[i + k] = '\0';
	if (i > n)
		return (j + n);
	return (i + j);
}
*/

/*
if (!dest || !src || n ==0)
		return (0);
#include<stdio.h>
int main ()
{
	char str[] = "BlackMama";
	char str1[] = "No,(G)-idle";
	int	str3[] = {1,2,3,4,5};
	int str4[] = {100,200,300,400};

	printf("처음 문자열 : %s\n", str);
	printf("%d\n",ft_strlcat(str, str1, 21));

	printf("다음 문자열 : %s\n", str);
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
