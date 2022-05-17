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
		masking_quote_flag(s, &flag); // 큰 따옴표인지, 작은 따옴표인지를 비트마스킹으로 체크함.
		if ((flag & BEGIN) == 0) // 만약에 BEGIN 플래그가 마킹되어있다면, 이는 시작점이라는 뜻. 시작점이 아니면 아래의 명령어들이 실행됨.
		{
			if (*s != ' ') // 공백은 전부 건너뛰고 새로운 문자가 나오는 순간 시작점으로 취급.
				flag |= BEGIN;
			if (*s == '<' || *s == '>') // 공백이고 뭐고 상관없이 일단 리다이렉트가 오면 체크.
				flag |= REDIR;
		}
		else
			count_on_flag(s, &flag, &cnt); // 앞에서 설정한 플래그 대로 세기 시작.
		++s;
	}
	if (flag & BEGIN)
		return (cnt + 1);
	else
		return (cnt);
}
