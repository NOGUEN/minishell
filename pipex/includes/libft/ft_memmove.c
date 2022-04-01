/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:51:49 by soekim            #+#    #+#             */
/*   Updated: 2020/11/19 16:43:03 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*dst_tab;
	char	*src_tab;
	int		i;

	if (!dst && !src)
		return (0);
	i = (int)len;
	dst_tab = (char *)dst;
	src_tab = (char *)src;
	if (dst_tab > src_tab)
		while (--i >= 0)
			dst_tab[i] = src_tab[i];
	else
	{
		while (--i >= 0)
		{
			*dst_tab = *src_tab;
			dst_tab++;
			src_tab++;
		}
	}
	return (dst);
}
