/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:44:51 by soekim            #+#    #+#             */
/*   Updated: 2021/07/02 15:52:55 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_and_move(char **target, char **src)
{
	while (**src)
	{
		**target = **src;
		++(*target);
		++(*src);
	}
	return ;
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	char	*join;

	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ret = join;
	if (s1)
		copy_and_move(&join, &s1);
	if (s2)
		copy_and_move(&join, &s2);
	*join = '\0';
	return (ret);
}
