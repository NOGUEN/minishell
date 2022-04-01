/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 12:35:02 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/04 11:30:15 by nogeun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	const char		*str;

	str = s;
	while (*s)
		s++;
	if (c == 0)
		return ((char *)s);
	while (s >= str)
	{
		if (*s == c)
			return ((char *)s);
		s--;
	}
	return (0);
}
