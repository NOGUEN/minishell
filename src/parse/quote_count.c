/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   quote_count.c                                      :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: noguen <marvin@42.fr>					  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/05/12 19:55:06 by noguen			#+#	#+#			 */
/*   Updated: 2022/05/13 13:44:19 by noguen           ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

char	*find_env(char *str, char **envp)
{
	int		len;
	char	**tmp;

	len = ft_strlen(str);
	tmp = envp;
	while (*tmp)
	{
		if (ft_strncmp(str, *tmp, len) == 0)
			return (*tmp);
		tmp++;
	}
	return (NULL);
}

int	env_len(char *cmd, int *size, char **envp)
{
	int		index;
	char	*status;

	printf("%s\n", cmd);
	index = 0;
	if (cmd[1] == '?')
	{
		status = ft_itoa(g_exit_status);
		*size += ft_strlen(status);
		free(status);
		return (1);
	}
	if (cmd[1] == '\0' || cmd[1] == '\"')
	{
		*size += 1;
		return (0);
	}
	index = get_env_key_size(cmd);
	printf("size: %d\n", *size);
	*size += get_env_value_size(cmd, index, envp);
	printf("size: %d\n", *size);
	return (index);
}

int	dquote_cnt(char *cmd, int *size, char **envp)
{
	int		index;
	char	*tmp;

	index = 1;
	while (cmd[index] && cmd[index] != '\"')
	{
		if (cmd[index] == '$')
		{
			index += (env_len(&cmd[index], size, envp) + 1);
		}
		else
		{
			++index;
			++(*size);
		}
	}
	return (index);
}

int	squote_cnt(char *cmd, int *size)
{
	int	index;

	index = 1;
	while (cmd[index] && cmd[index] != '\'')
	{
		++index;
		++(*size);
	}
	return (index);
}
