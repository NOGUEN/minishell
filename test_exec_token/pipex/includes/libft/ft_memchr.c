/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:51:49 by soekim            #+#    #+#             */
/*   Updated: 2020/11/16 20:28:25 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	int				i;

	i = (int)n;
	str = (unsigned char *)s;
	while (--i >= 0)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
	}
	return ((void *)0);
}
