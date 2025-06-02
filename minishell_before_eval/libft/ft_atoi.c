/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:25:44 by djang             #+#    #+#             */
/*   Updated: 2024/02/26 12:25:46 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	intnum;
	int	countminus;

	countminus = 1;
	intnum = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			countminus = countminus * -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		intnum = intnum * 10 + (*str - 48);
		str++;
	}
	return (intnum * countminus);
}

/*
#include <stdio.h>
#include <stdlib.h>    // atoi included

int main()
{
    char *s1 = "        --283dfg";   // "283" is str
    int num1;

    num1 = ft_atoi(s1);        // string to int, convert and  assign num1

    printf("%d\n", num1);   // 283

    return 0;
}
*/