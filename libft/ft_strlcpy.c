/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:09:35 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/03 12:02:53 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!src || !dst)
		return (0);
	while (src[j] && j < dstsize - 1 && dstsize > 0)
	{
		dst[j] = src[j];
		j++;
	}
	if (dstsize - j > 0)
		dst[j] = '\0';
	while (src[i])
		i++;
	return (i);
}
