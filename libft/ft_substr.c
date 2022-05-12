/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:44:51 by soekim            #+#    #+#             */
/*   Updated: 2020/11/24 00:20:41 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if ((int)start >= i)
		i = 0;
	else if ((int)start + (int)len >= i)
		i -= ((int)start);
	else
		i = (int)len;
	sub = (char *)malloc(i + 1);
	if (!sub)
		return ((void *)0);
	sub[i] = '\0';
	while (i-- > 0)
		sub[i] = s[(int)start + i];
	return (sub);
}
