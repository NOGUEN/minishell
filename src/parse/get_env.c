/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: noguen <marvin@42.fr>					  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/05/12 19:55:53 by noguen			#+#	#+#			 */
/*   Updated: 2022/05/13 13:17:48 by noguen           ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

char	*get_env_value(char *key, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(key, envp[i], ft_strlen(key))
			&& envp[i][ft_strlen(key)] == '=')
			return (envp[i] + ft_strlen(key) + 1);
	}
	return (NULL);
}

int	get_env_key(char *src, char **key)
{
	int	key_len;

	key_len = get_env_key_size(src);
	*key = ft_substr(src, 1, key_len);
	printf("cut key: %s\n", *key);
	printf("cut key len : %d\n", key_len);
	return (key_len);
}

int	get_env_key_size(char *str)
{
	int	index;

	printf("key_size: %s\n", str);
	index = 0;
	if (ft_isdigit(str[1]))
		return (1);
	while (str[++index])
	{
		if (!(ft_isalnum(str[index]) || str[index] == '_'))
			return (index - 1);
	}
	return (index - 1);
}

int	get_env_value_size(char *str, int size, char **envp)
{
	int	index;

	index = -1;
	while (envp[++index])
		if ((!ft_strncmp(&str[1], envp[index], size)) && envp[index][size] == '=')
			return (ft_strlen(envp[index] + size + 1));
	return (0);
}
