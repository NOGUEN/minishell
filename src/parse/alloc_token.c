/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:43:26 by noguen            #+#    #+#             */
/*   Updated: 2022/05/15 14:03:00 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

int	alloc_d_quote_cnt(char *src, char **dest, char **envp)
{
	int	index;

	index = 1;
	while (src[index] && src[index] != '\"')
	{
		if (src[index] == '$')
			index += (alloc_env(&src[index], dest, envp) + 1);
		else
		{
			**dest = src[index];
			(*dest)++;
			++index;
		}
	}
	return (index);
}

int	alloc_s_quote_cnt(char *src, char **dest)
{
	int	src_index;
	int	dest_length;

	src_index = 0;
	dest_length = 0;
	while (src[++src_index] && src[src_index] != '\'')
		dest_length++;
	ft_memcpy(*dest, src + 1, dest_length);
	*dest += dest_length;
	return (src_index);
}

void	cmd_copy(char *src, char *dest, char **envp)
{
	int		src_index;
	int		size;
	char	*dest_end;

	size = 0;
	src_index = -1;
	dest_end = dest;
	while (src[++src_index])
	{
		if (src[src_index] == '\''
			&& check_unclosed_quote(&src[src_index], '\''))
			src_index += alloc_s_quote_cnt(&src[src_index], &dest_end); // 큰따옴표가 올 경우 복사하는 함수
		else if (src[src_index] == '\"'
			&& check_unclosed_quote(&src[src_index], '\"'))
			src_index += alloc_d_quote_cnt(&src[src_index], &dest_end, envp); // 작은따옴표가 올 경우 복사하는 함수
		else if (src[src_index] == '$')
			src_index += alloc_env(&src[src_index], &dest_end, envp); // 환경변수 표시가 오면 해당 key값대로 복사하는 함수
		else if (src[src_index]) // 그 외의 것들을 복사해서 넣어주는 구문
		{
			*dest_end = src[src_index]; 
			dest_end++;
		}
	}
	*dest_end = '\0';
}

t_token	*alloc_token(t_token *token, char **envp)
{
	int		cmd_len;
	size_t	i;
	char	*tmp_cmd;

	i = 0;
	while (token[i].cmd)
	{
		cmd_len = 0;
		tmp_cmd = token[i].cmd;
		cmd_len = get_parse_size(tmp_cmd, envp); // 문자열의 크기를 구해야함. 환경변수의 경우 key값으로 들어오기 때문에 실제 value의 길이와 다름.
		if (token[i].cmd[0] == '<' || token[i].cmd[0] == '>') // 라다이렉트 체크.
		{
			if (check_redir(token[i].cmd))
				token[i].redir_flag = 1;
			else
				token[i].redir_flag = -1;
		}
		token[i].cmd = (char *)malloc(sizeof(char) * (cmd_len + 1)); // 토큰의 커맨드들을 받아온 파싱 사이즈 만큼 할당해줌.
		cmd_copy(tmp_cmd, token[i].cmd, envp); // 파싱 사이즈만큼 할당했다면 이제 명령어들을 복사해서 값을 넣어줌. 환경변수의 경우 환경변수 값을 찾아서 넣음.
		free(tmp_cmd); // 임시로 사용한 문자열은 get_parse_size와 cmd_copy이후에는 더 쓸 일이 없으므로 할당해제해줌.
		i++;
	}
	return (token);
}
