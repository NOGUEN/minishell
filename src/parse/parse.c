/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:44:35 by noguen            #+#    #+#             */
/*   Updated: 2022/05/15 17:27:39 by hnoh             ###   ########.fr       */
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

	parse_set(&index, &begin, &flag); // 변수 초기화. PIPE 플래그의 경우 체크 되어있는게 기본.
	while (1)
	{
		parse_set2(index, &flag, line); // QUOTE가 처음 나온 거라면 flag에 QUOTE 비트 마스킹. 두번째로 나온거라면 QUOTE 비트마스킹 해제.
		if (line[index] == '\0' || (line[index] == '|' && (flag & QUOTE) == 0))
		{ // NULL 또는 PIPE가 QUOTE 플래그 마킹이 안된 상태로 나왔다면, 이는 명령의 끝을 의미함.
			parse_split1(line, index, &flag); // 파이프가 나왔다면 해당 문자를 널로 변환. 그게 아니면 PIPE 플래그 해제.
			new = new_cmd(&line[begin], flag, envp, begin); // 해당 플래그와 시작점(명령어 시작)을 받아서 새 명령어 구조체를 만듦. new_cmd.c에 함수 정의됨.
			if (new == NULL) // 널가드
				return ;
			parse_split2(cmds, &tmp, new, begin); // 파이프가 있었다면 뒤의 명령어를 파이프로 이어줘야하므로, 연결리스트로 이어줌.
			if ((flag & PIPE) == 0) // 파이프가 없다면 그대로 종료.
				break ;
			begin = index + 1; // 여기까지 왔다는 것은 파이프가 없다는 것이므로 종료하지 않고 시작점을 현재 인덱스 다음으로 변경함.
		}
		++index; // 인덱스 하나 증가 시킴.
	}
	*cmds = tmp; // 연결리스트 끝맺음.
}
