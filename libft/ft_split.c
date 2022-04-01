/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:16:00 by hnoh              #+#    #+#             */
/*   Updated: 2021/01/07 11:27:18 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *s, char c)
{
	char	flag;
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	flag = 1;
	while (*s)
	{
		if (*s == c)
			flag = 1;
		else
		{
			(flag == 1) ? count++ : count;
			flag = 0;
		}
		s++;
	}
	return (count);
}

static void		ft_free(char **ret)
{
	int		i;

	i = 0;
	while (ret[i])
	{
		free(ret[i]);
		i++;
	}
	free(ret);
}

char			**ft_split(char const *s, char c)
{
	const size_t	wordcnt = ft_wordcount(s, c);
	const char		*p = s;
	char			**ret;
	char			*end;
	size_t			i;

	if (!s || !(ret = ft_calloc(wordcnt + 1, sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < wordcnt)
	{
		if (*s != c)
		{
			if (!(end = ft_strchr(s, c)))
				end = (char *)p + ft_strlen(p);
			if (!(ret[i++] = ft_strndup(s, end - s)))
			{
				ft_free(ret);
				return (NULL);
			}
			s = end;
		}
		s++;
	}
	return (ret);
}
