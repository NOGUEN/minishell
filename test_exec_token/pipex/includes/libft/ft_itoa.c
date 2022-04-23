/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <soekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 03:59:01 by soekim            #+#    #+#             */
/*   Updated: 2020/11/20 15:40:40 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(int n)
{
	int	temp;
	int	len;

	if (n > 0)
	{
		temp = (long long int)n;
		len = 0;
	}
	else
	{
		temp = -(long long int)n;
		len = 1;
	}
	while (temp != 0)
	{
		len++;
		temp /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long long int	temp;
	int				len;
	char			*arr;

	len = get_len(n);
	arr = (char *)malloc(len + 1);
	if (!arr)
		return (0);
	if (n < 0)
		arr[0] = '-';
	else
		arr[0] = '0';
	if (n < 0)
		temp = -(long long int)n;
	else
		temp = (long long int)n;
	arr[len] = '\0';
	while (temp > 0)
	{
		len--;
		arr[len] = temp % 10 + '0';
		temp /= 10;
	}
	return (arr);
}
