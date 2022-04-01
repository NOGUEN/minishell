/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 13:42:11 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/04 11:27:44 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*source;
	char	*dest;

	dest = (char *)dst;
	source = (char *)src;
	if (!dst && !src)
		return (dst);
	while (n--)
		*dest++ = *source++;
	return (dst);
}
