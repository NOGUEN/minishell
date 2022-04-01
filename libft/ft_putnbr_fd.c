/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 12:12:22 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/04 12:20:57 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int i;

	if (n >= 0)
	{
		i = n;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		i = (unsigned int)(n * -1);
	}
	if (i > 9)
		ft_putnbr_fd(i / 10, fd);
	ft_putchar_fd((char)(i % 10 + '0'), fd);
}
