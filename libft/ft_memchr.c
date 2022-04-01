/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:02:43 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/04 10:06:17 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	c2;
	size_t			i;

	i = 0;
	c2 = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (str[i] == c2)
			return (str + i);
		i++;
	}
	return (NULL);
}
