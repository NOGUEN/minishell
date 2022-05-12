/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:44:51 by soekim            #+#    #+#             */
/*   Updated: 2020/11/22 18:25:51 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*c1;
	unsigned char	*c2;

	i = (int)n;
	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (--i >= 0 && *c1 == *c2 && *c1 != '\0' && *c2 != '\0')
	{
		c1++;
		c2++;
	}
	if (i < 0)
		return (0);
	return ((int)(*c1 - *c2));
}
