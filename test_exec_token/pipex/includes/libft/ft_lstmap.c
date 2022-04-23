/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:18:06 by soekim            #+#    #+#             */
/*   Updated: 2020/11/22 17:11:09 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*lst_alloc_fails(t_list *head, void (*del)(void *))
{
	if (head && del)
		ft_lstclear(&head, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*curr;

	if (!lst || !f || !del)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (!head)
		return (NULL);
	curr = head;
	while (lst->next)
	{
		lst = lst->next;
		curr->next = ft_lstnew(f(lst->content));
		if (!curr->next)
			return (lst_alloc_fails(head, del));
		curr = curr->next;
	}
	return (head);
}
