/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:08:03 by soekim            #+#    #+#             */
/*   Updated: 2020/11/20 15:41:20 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*ret;

	if (!s || !f)
		return (0);
	len = 0;
	while (s[len])
		len++;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return ((void *)0);
	ret[len] = '\0';
	while (--len >= 0)
		ret[len] = f((unsigned int)len, s[len]);
	return (ret);
}
