/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:24:06 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:24:08 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return ((char *)str + i);
	return (0);
}

/*
#include<stdio.h>
int main ()
{
	char* str = "kakao";
	char* ptr = ft_strchr(str, 'a');
	//while(ptr != '\0')
	//{
		printf("찾는 문자 : , 찾은 문자열 : %s\n",  ptr);
		//ptr = ft_strchr(ptr + 1, 'o');
	//}
}
*/