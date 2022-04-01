/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:04:04 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/04 13:16:02 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;

	tmp = ft_lstnew(f(lst->content));
	new = tmp;
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		if (!(tmp->next = ft_lstnew(f(lst->content))))
		{
			ft_lstdelone(tmp->next, del);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (new);
}
