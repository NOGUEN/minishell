/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:14:08 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/03 12:01:41 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		destln;
	size_t		srcln;

	srcln = ft_strlen(src);
	destln = ft_strlen(dst);
	j = destln;
	i = 0;
	if (destln < size - 1 && size > 0)
	{
		while (src[i] && destln + i < size - 1)
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = 0;
	}
	if (destln >= size)
		destln = size;
	return (destln + srcln);
}
