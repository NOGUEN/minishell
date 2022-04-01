/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:51:49 by soekim            #+#    #+#             */
/*   Updated: 2020/11/19 16:42:17 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_tab;
	char	*src_tab;
	int		i;

	if (!dst && !src)
		return ((void *)0);
	i = (int)n;
	dst_tab = (char *)dst;
	src_tab = (char *)src;
	while (--i >= 0)
		dst_tab[i] = src_tab[i];
	return (dst);
}
