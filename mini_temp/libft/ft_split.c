/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:41:00 by djang             #+#    #+#             */
/*   Updated: 2024/02/28 18:41:02 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_s_c(char const *s, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 1;
	while (s[i])
	{
		if (s[i] == c)
			k++;
		i++;
	}
	return (k);
}

char	*ft_strdupc(const char *str, char c, int n)
{
	char	*dest;
	int		len;
	int		i;

	len = 0;
	while (str[n + len] && str[n + len] != c)
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = str[i + n];
		i++;
	}
	dest[len] = 0;
	return (dest);
}

void	ft_get_free(char **s, int i)
{
	while (i)
	{
		free(s[i]);
		s[i] = NULL;
		i--;
	}
	free(s);
	s = NULL;
}

char	**ft_innersplit(char const *s, char c, char **dest)
{
	int		line;
	int		i;

	i = 0;
	line = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			dest[line] = ft_strdupc(s, c, i);
			if (!(dest[line]))
			{
				ft_get_free(dest, line - 1);
				return (0);
			}
			line++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	dest[line] = 0;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		wordcount;

	wordcount = check_s_c(s, c);
	dest = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!dest)
		return (0);
	dest = ft_innersplit(s, c, dest);
	return (dest);
}

/*
char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		wordcount;
	int		line;
	int		i;

	wordcount = check_s_c(s, c);
	i = 0;
	line = 0;
	dest = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!dest)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			dest[line] = ft_strdupc(s, c, i);
			line++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	dest[line] = 0;
	return (dest);
}
*/

/*
#include<stdio.h>
int	main ()
{
	char *s;
	char a;
	s = "kakao";
	a = 'a';
	char **k = ft_split(s,a);
	//printf("%s/n", ft_split(s,a));
	int i = 0;

	while (k[i] != 0)
	{	
		printf("%s\n", k[i]);
		i++;
	}
	//printf("%s ", k[0]);
	return 0;
}
*/