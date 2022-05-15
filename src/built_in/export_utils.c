/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:17:18 by noguen            #+#    #+#             */
/*   Updated: 2022/05/15 20:12:21 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

int	is_valid_export(char *line)
{
	char	**str_arr;
	char	*key;
	int		i;
	int		ret;

	str_arr = ft_split(line, '=');
	key = str_arr[0];
	i = -1;
	ret = is_valid_key(key);
	while (str_arr[++i])
		free(str_arr[i]);
	free(str_arr);
	return (ret);
}

int	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (ft_strlen(key) == 0)
		return (0);
	while (key[i])
	{
		if (ft_isdigit(key[0]))
			return (0);
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (TRUE);
}

char	**find_existing_var(char *token, char **envp)
{
	char	*token_sep;
	char	*env_sep;
	char	**existing;

	existing = NULL;
	token_sep = ft_strchr(token, '=');
	if (token_sep)
		*token_sep = '\0';
	while (*envp && existing == NULL)
	{
		env_sep = ft_strchr(*envp, '=');
		if (env_sep)
			*env_sep = '\0';
		if (!ft_strcmp(token, *envp))
			existing = envp;
		if (env_sep)
			*env_sep = '=';
		++envp;
	}
	if (token_sep)
		*token_sep = '=';
	return (existing);
}
