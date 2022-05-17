/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:46:07 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 16:10:39 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

t_cmd	*new_cmd(char *line, int pipe_flag, char **envp, int exit_flag)
{
	t_cmd	*result;

	result = (t_cmd *)malloc(sizeof(t_cmd)); // 일단 구조체를 동적할당함.
	if (result == NULL) // 널가드.
		return (NULL);
	result->tokens = split_cmd(line); // 명령어들을 쪼갬.
	alloc_token(result->tokens, envp); // 쪼갠 명령어들을 토대로 토큰들을 할당함. 이게 필요한 이유는 환경변수들의 key값을 value값으로 변경해서 할당해야하기 때문. alloc_token.c에 정의됨.
	result->pipe_flag = pipe_flag; // 파이프가 있냐 없냐를 넘겨줌.
	if (exit_flag == 0 && pipe_flag == 0) // 파이프가 없는데, 종료 flag에 값이 마킹되어있지 않다면 마킹해줌.
		result->exit_flag = 1;
	else
		result->exit_flag = 0;
	result->next = NULL; // 일단 연결리스트 끝맺음.
	return (result); // 해당 명령어 구조체를 넘겨줌.
}
