/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parse_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:44:18 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 17:09:39 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

int	get_parse_size(char *cmd, char **envp)
{
	int		size;
	int		index;

	size = 0;
	index = -1;
	while (cmd[++index])
	{
		if (cmd[index] == '\'' && check_unclosed_quote(&cmd[index], '\'')) // 만약에 해당 따옴표가 닫혀있는 따옴표라면, 그 안의 문자열 수를 셈.
			index += squote_cnt(&cmd[index], &size); // 아래의 두 함수를 포함해서, 이 함수들은 인덱스 값을 반환함.
		else if (cmd[index] == '\"' && check_unclosed_quote(&cmd[index], '\"')) // 만약에 해당 따옴표가 닫혀있는 큰 따옴표라면, 그 안의 문자열 수를 셈.
			index += dquote_cnt(&cmd[index], &size, envp);
		else if (cmd[index] == '$') // 환경변수의 경우 해당 환경변수의 value의 크기를 얻어냄.
			index += env_len(&cmd[index], &size, envp);
		else if (cmd[index]) // 그냥 문자라면 단순히 세어주고 끝.
			++size;
	}
	return (size); // 크기 반환.
}
