/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:03:58 by soekim            #+#    #+#             */
/*   Updated: 2020/11/22 16:09:59 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*to_free;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		to_free = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(to_free, del);
	}
	return ;
}
