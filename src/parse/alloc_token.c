/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:43:26 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 15:10:16 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

int	alloc_env(char *src, char **dest, char **envp)
{
	char	*status;
	char	*key;
	char	*env_val;
	int		env_len;
	int		index;

	index = 0;
	if (src[1] == '?')
	{
		status = ft_itoa(g_exit_status);
		ft_memcpy(*dest, status, ft_strlen(status));
		*dest += ft_strlen(status);
		free(status);
		return (1);
	}
	else if (src[1] == '\0' || src[1] == '\"')
	{
		**dest = '$';
		*dest += 1;
		return (0);
	}
	key = NULL;
	index += get_env_key(src, &key);
	env_val = get_env_value(key, envp);
	env_len = ft_strlen(env_val);
	ft_memcpy(*dest, env_val, env_len);
	*dest += env_len;
	free(key);
	return (index);
}

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
			src_index += alloc_s_quote_cnt(&src[src_index], &dest_end);
		else if (src[src_index] == '\"'
			&& check_unclosed_quote(&src[src_index], '\"'))
			src_index += alloc_d_quote_cnt(&src[src_index], &dest_end, envp);
		else if (src[src_index] == '$')
			src_index += alloc_env(&src[src_index], &dest_end, envp);
		else if (src[src_index])
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
		cmd_len = get_parse_size(tmp_cmd, envp);
		if (token[i].cmd[0] == '<' || token[i].cmd[0] == '>')
		{
			if (check_redir(token[i].cmd))
				token[i].redir_flag = 1;
			else
				token[i].redir_flag = -1;
		}
		token[i].cmd = (char *)malloc(sizeof(char) * (cmd_len + 1));
		cmd_copy(tmp_cmd, token[i].cmd, envp);
		free(tmp_cmd);
		i++;
	}
	return (token);
}
