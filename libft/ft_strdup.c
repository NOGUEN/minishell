/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:29:26 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/04 10:32:19 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s)
{
	char	*str;
	int		len;

	len = ft_strlen(s) + 1;
	if ((str = malloc(len)))
	{
		ft_strlcpy(str, s, len);
		return (str);
	}
	return (NULL);
}
