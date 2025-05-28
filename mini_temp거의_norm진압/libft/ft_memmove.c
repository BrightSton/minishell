/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:20:50 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:20:52 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*temp;
	size_t		i;

	if (!src && !dest)
		return (NULL);
	temp = dest;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			temp[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			temp[n - 1] = ((char *)src)[n - 1];
			n--;
		}
	}
	return (dest);
}

/*
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*temp;
	const char	*s;
	size_t		i;

	if (!src && !dest)
		return (NULL);
	temp = dest;
	s = src;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			temp[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			temp[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
*/

/*
#include<stdio.h>
int main ()
{	
	char	src[] = "lorem ipsum dolor sit amet";
	char	*dest;
	dest = src + 1;
	// char str[] = "BlackMama";
	// char str1[] = "No,(G)-idle";
	// int	str3[] = {1,2,3,4,5};
	// int str4[] = {100,200,300,400};

	printf("처음 문자열 : %s\n", src);
	ft_memmove(dest, "consectetur", 5);
	write(1, dest, 22);
	//printf("다음 문자열 : %s\n", dest);
	//char* ptr = ft_strrchr(str, 'a');
	//while(ptr != '\0')
	//{
	//	printf("찾는 문자 : %c, 찾은 문자열 : %s\n", *ptr, ptr);
		//ptr = ft_strchr(ptr + 1, 'o');
	//}
	// printf("\n");
	// printf("처음 문자열 : %d\n", str3[0]);
	// printf("다음 문자열 : %d\n", str3[1]);
	// printf("다음 문자열 : %d\n", str3[2]);
	// printf("다음 문자열 : %d\n", str3[3]);
	// printf("다음 문자열 : %d\n", str3[4]);
	// ft_memmove(str3, str4, sizeof(int) *4);
	// printf("\n");
	// printf("다음 문자열 : %d\n", str3[0]);
	// printf("다음 문자열 : %d\n", str3[1]);
	// printf("다음 문자열 : %d\n", str3[2]);
	// printf("다음 문자열 : %d\n", str3[3]);
	// printf("다음 문자열 : %d\n", str3[4]);
}
*/