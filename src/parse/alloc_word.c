/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:45:26 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 15:33:17 by hnoh             ###   ########.fr       */
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

	len = word_len(*s); // 단어의 길이를 얻어내는 함수.
	word = (char *)malloc(sizeof(char) + (len + 1)); // 얻어낸 단어의 길이대로 할당해줌.
	if (word == NULL) // 널가드
		return (NULL);
	i = -1;
	while (++i < len) // 단어의 길이만큼 할당한 문자열에 값을 복사해서 넣어줌.
	{
		word[i] = **s;
		(*s)++;
	}
	word[i] = '\0'; // 문자열 끝맺음.
	return (word);
}
