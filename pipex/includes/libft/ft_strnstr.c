/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 21:50:58 by soekim            #+#    #+#             */
/*   Updated: 2020/11/24 01:00:50 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	length;

	if (!(*needle))
		return ((char *)haystack);
	length = 0;
	while (length < len && haystack[length])
	{
		i = 0;
		while ((haystack[length + i] == needle[i]) && needle[i])
			i++;
		if (!(needle[i]) && length + i <= len)
			return ((char *)(haystack + length));
		length++;
	}
	return ((void *)0);
}
