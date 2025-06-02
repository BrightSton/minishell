/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 03:00:32 by djang             #+#    #+#             */
/*   Updated: 2024/03/03 03:00:33 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*dest;

	dest = NULL;
	while (lst)
	{
		temp = ft_lstnew(f(lst ->content));
		if (!temp)
		{
			ft_lstclear(&dest, del);
			return ((void *)0);
		}
		ft_lstadd_back(&dest, temp);
		lst = lst ->next;
	}
	temp = NULL;
	return (dest);
}
