/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:36:30 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/04 10:40:56 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*a;
	size_t	b;

	b = 0;
	if (!s)
		return (NULL);
	if (!(a = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (ft_strlen(s) > start)
	{
		while (s[start + b] && b < len)
		{
			a[b] = s[start + b];
			b++;
		}
	}
	a[b] = '\0';
	return (a);
}
