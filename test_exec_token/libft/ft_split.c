/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <soekim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 13:24:08 by soekim            #+#    #+#             */
/*   Updated: 2020/11/22 18:25:20 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordcount(const char *s, char c)
{
	int		wordnum;

	if (!s)
		return (-1);
	wordnum = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s)
			wordnum++;
		while (*s != c && *s)
			s++;
	}
	return (wordnum);
}

static int	wdalloc(const char *str, char c, int wordnum, char **ret)
{
	int		count;
	int		i;

	count = 0;
	if (!(*str))
		return (0);
	while (str[count] != c && str[count])
		count++;
	ret[wordnum] = (char *)malloc(count + 1);
	if (!ret[wordnum])
		return (-1);
	ret[wordnum][count] = '\0';
	i = -1;
	while (++i < count)
		ret[wordnum][i] = str[i];
	return (count);
}

static void	*splfree_null(char ***tofree, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		free((*tofree)[i]);
		i++;
	}
	free(*tofree);
	return ((void *)0);
}

char	**ft_split(char const *s, char c)
{
	int		wordnum;
	int		wordlen;
	char	*tab;
	char	**ret;

	if (!s)
		return (0);
	wordnum = wordcount(s, c);
	ret = (char **)malloc((wordnum + 1) * sizeof(char *));
	if (!ret)
		return ((void *)0);
	ret[wordnum] = (void *)0;
	tab = (char *)s;
	wordnum = 0;
	while (*tab)
	{
		while (*tab == c)
			tab++;
		wordlen = wdalloc(tab, c, wordnum, ret);
		if (wordlen < 0)
			return (splfree_null(&ret, wordnum));
		tab += wordlen;
		wordnum++;
	}
	return (ret);
}
