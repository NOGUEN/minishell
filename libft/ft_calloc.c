/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:51:49 by soekim            #+#    #+#             */
/*   Updated: 2020/11/22 18:18:38 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	long long int	i;
	void			*memory;
	char			*tab;

	i = (int)count * (int)size;
	memory = malloc(i);
	if (!memory)
		return (0);
	tab = (char *)memory;
	while (--i >= 0)
		tab[i] = 0;
	return (memory);
}
