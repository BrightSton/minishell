/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:00:07 by djang             #+#    #+#             */
/*   Updated: 2024/03/03 03:00:08 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (*lst != NULL)
	{
		temp = (*lst)-> next;
		del((*lst)-> content);
		free(*lst);
		*lst = temp;
	}
}

/*
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;

	while (*lst != NULL)
	{
		temp = (*lst) ->next;
		ft_lstdelone(*lst,del);
		*lst = temp;
	}
}
*/