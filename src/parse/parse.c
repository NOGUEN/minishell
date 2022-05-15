/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:44:35 by noguen            #+#    #+#             */
/*   Updated: 2022/05/15 17:27:20 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

void	parse_set(int *index, int *begin, int *flag)
{
	*index = 0;
	*begin = 0;
	*flag = PIPE;
}

void	parse_set2(int index, int *flag, char *line)
{
	if ((line[index] == '\"' || line[index] == '\'') && ((*flag) & QUOTE) == 0)
		(*flag) |= QUOTE;
	else if ((line[index] == '\"' || line[index] == '\'')
		&& (*flag & QUOTE) != 0)
		(*flag) &= !QUOTE;
}

void	parse_split1(char *line, int index, int *flag)
{
	if (line[index] == '|')
	{
		line[index] = '\0';
	}
	else
		(*flag) &= !PIPE;
}

void	parse_split2(t_cmd **cmds, t_cmd **tmp, t_cmd *new, int begin)
{
	if (begin == 0)
	{
		*cmds = new;
		*tmp = *cmds;
	}
	else
	{
		(*cmds)->next = new;
		*cmds = (*cmds)->next;
	}
}

void	parse(t_cmd **cmds, char *line, char **envp)
{
	int		index;
	int		begin;
	int		flag;
	t_cmd	*new;
	t_cmd	*tmp;

	parse_set(&index, &begin, &flag);
	while (1)
	{
		parse_set2(index, &flag, line);
		if (line[index] == '\0' || (line[index] == '|' && (flag & QUOTE) == 0))
		{
			parse_split1(line, index, &flag);
			new = new_cmd(&line[begin], flag, envp, begin);
			if (new == NULL)
				return ;
			parse_split2(cmds, &tmp, new, begin);
			if ((flag & PIPE) == 0)
				break ;
			begin = index + 1;
		}
		++index;
	}
	*cmds = tmp;
}
