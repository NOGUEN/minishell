/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:51:49 by soekim            #+#    #+#             */
/*   Updated: 2020/11/18 18:44:04 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_tab;
	unsigned char	*src_tab;
	size_t			i;

	dst_tab = (unsigned char *)dst;
	src_tab = (unsigned char *)src;
	i = 0;
	while (i < n && *src_tab != (unsigned char)c)
	{
		*dst_tab = *src_tab;
		dst_tab++;
		src_tab++;
		i++;
	}
	if (i == n)
		return ((void *)0);
	while (*src_tab == (unsigned char)c)
	{
		*dst_tab = *src_tab;
		dst_tab++;
		src_tab++;
	}
	return ((void *)dst_tab);
}
