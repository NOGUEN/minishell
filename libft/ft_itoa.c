/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:23:56 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/07 13:27:01 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_get_digit_count(long int n)
{
	int		i;

	if (n < 0)
		n *= -1;
	i = 1;
	while (n > 9)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				digit_count;
	long int		long_n;

	long_n = n;
	digit_count = ft_get_digit_count(long_n);
	if (long_n < 0)
		digit_count++;
	if (!(str = malloc((digit_count + 1) * sizeof(char))))
		return (NULL);
	str[0] = '0';
	if (long_n < 0)
	{
		str[0] = '-';
		long_n *= -1;
	}
	str[digit_count] = '\0';
	while (((digit_count >= 0 && str[0] != '-')
				|| (digit_count > 0 && str[0] == '-')) && long_n != 0)
	{
		str[digit_count - 1] = (long_n % 10) + '0';
		long_n /= 10;
		digit_count--;
	}
	return (str);
}
