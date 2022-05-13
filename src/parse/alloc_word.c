/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:45:26 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 00:45:27 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

int	redir_len(char const **s, int *len)
{
	if ((**s) == '>' || (**s) == '<')
	{
		while (**s)
		{
			if ((**s) == '>' || (**s) == '<')
				(*len)++;
			else
				return (*len);
			(*s)++;
		}
	}
	return (*len);
}

int	count_word_len_on_flag(char const *s, int *len, int *flag)
{
	if ((*flag & BEGIN) == 0)
	{
		if (*s != ' ')
		{
			*flag |= BEGIN;
			(*len)++;
		}
	}
	else
	{
		if (*s == ' ' && (*flag & DQUOTE) == 0 && (*flag & SQUOTE) == 0)
			return (1);
		else if ((*s == '>' || *s == '<') && (*flag & DQUOTE) == 0
			&& (*flag & SQUOTE) == 0)
			return (1);
		else
			(*len)++;
	}
	return (0);
}

int	word_len(char const *s)
{
	int	len;
	int	flag;

	len = 0;
	flag = 0;
	if (redir_len(&s, &len) != 0)
		return (len);
	while (*s)
	{
		masking_quote_flag(s, &flag);
		if (count_word_len_on_flag(s, &len, &flag))
			break ;
		++s;
	}
	return (len);
}

char	*alloc_word(const char **s)
{
	int		len;
	int		i;
	char	*word;

	len = word_len(*s);
	word = (char *)malloc(sizeof(char) + (len + 1));
	if (word == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		word[i] = **s;
		(*s)++;
	}
	word[i] = '\0';
	return (word);
}
