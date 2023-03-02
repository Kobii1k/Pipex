/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:11:50 by mgagne            #+#    #+#             */
/*   Updated: 2022/12/02 13:04:03 by mgagne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_cpy;
	t_list	*lst_keep;

	if (!(f && lst && del))
		return (NULL);
	lst_cpy = NULL;
	while (lst)
	{
		lst_keep = ft_lstnew(f(lst->content));
		if (!lst_keep)
		{
			ft_lstclear(&lst_keep, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_cpy, lst_keep);
		lst = lst->next;
	}
	return (lst_cpy);
}
