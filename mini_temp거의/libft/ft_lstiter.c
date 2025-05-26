/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:00:20 by djang             #+#    #+#             */
/*   Updated: 2024/03/03 03:00:21 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst ->content);
		lst = lst ->next;
	}
}

/*
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	//list	temp;
	while(lst != NULL)
	{
		f(lst ->content);
		lst = lst ->next;
	}
}
*/