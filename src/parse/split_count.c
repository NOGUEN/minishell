/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:46:37 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 00:46:39 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

void	masking_quote_flag(char const *s, int *flag)
{
	if (*s == '\"')
	{
		if ((*flag) & DQUOTE)
			(*flag) &= !DQUOTE;
		else
			(*flag) |= DQUOTE;
	}
	else if (*s == '\'')
	{
		if ((*flag) & SQUOTE)
			(*flag) &= !SQUOTE;
		else
			(*flag) |= SQUOTE;
	}
}

void	count(int *flag, int *cnt, int make_begin_zero_flag)
{
	if (*flag & REDIR)
		*flag &= !REDIR;
	if (make_begin_zero_flag == 1)
		*flag &= !BEGIN;
	(*cnt)++;
}

void	count_on_flag(char const *s, int *flag, int *cnt)
{
	if (*s == ' ' && ((*flag & DQUOTE) == 0 && (*flag & SQUOTE) == 0))
		count(flag, cnt, 1);
	else if ((*s == '>' || *s == '<') && ((*flag & DQUOTE) == 0
			&& (*flag & SQUOTE) == 0))
	{
		if ((*flag & REDIR) == 0)
			(*cnt)++;
		*flag |= REDIR;
	}
	else if (*s != ' '
		&& !(*s == '>' || *s == '<')
		&& ((*flag & DQUOTE) == 0 && (*flag & SQUOTE) == 0)
		&& (*(s - 1) == '>' || *(s - 1) == '<'))
		count(flag, cnt, 0);
	else if (*s == '\'' && *flag & SQUOTE)
		count(flag, cnt, 0);
	else if (*s == '\"' && *flag & DQUOTE)
		count(flag, cnt, 0);
}

int	split_count(char const *s)
{
	int	cnt;
	int	flag;

	cnt = 0;
	flag = 0;
	while (*s)
	{
		masking_quote_flag(s, &flag);
		if ((flag & BEGIN) == 0)
		{
			if (*s != ' ')
				flag |= BEGIN;
			if (*s == '<' || *s == '>')
				flag |= REDIR;
		}
		else
			count_on_flag(s, &flag, &cnt);
		++s;
	}
	if (flag & BEGIN)
		return (cnt + 1);
	else
		return (cnt);
}
