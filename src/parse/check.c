/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 00:43:59 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 00:44:01 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

int	check_whitespace(char *line)
{
	int	len;
	int	i;

	len = ft_strlen(line);
	i = -1;
	while (++i < len)
	{
		if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			return (0);
	}
	return (1);
}

int	check_redir(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (len > 2)
		return (0);
	if (!ft_strncmp("<<", cmd, len) || !ft_strncmp(">>", cmd, len)
		|| !ft_strncmp("<", cmd, len) || !ft_strncmp(">", cmd, len))
		return (1);
	else
		return (0);
}

int	check_unclosed_quote(char *str, char quote)
{
	int	index;

	index = 1;
	while (str[index] && str[index] != quote)
		index++;
	if (str[index] == '\0')
		return (0);
	return (1);
}
