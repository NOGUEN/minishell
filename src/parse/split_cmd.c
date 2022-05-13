/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: noguen <marvin@42.fr>					  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/05/12 18:55:03 by noguen			#+#	#+#			 */
/*   Updated: 2022/05/13 13:12:57 by noguen           ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

void	*free_cmd(t_token *result, int len)
{
	int	i;

	i = 0;
	while (i < len)
		free(result[i++].cmd);
	return (NULL);
}

t_token	*split_cmd(char const *s)
{
	int		result_index;
	t_token	*result;

	if (s == NULL)
		return (NULL);
	result_index = 0;
	result = malloc(sizeof(t_token) * (split_count(s) + 1));
	if (result == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == ' ')
			++s;
		else
		{
			result[result_index].cmd = alloc_word(&s);
			result[result_index].redir_flag = 0;
			if (result[result_index].cmd == NULL)
				return (free_cmd(result, result_index));
			++result_index;
		}
	}
	result[result_index].cmd = 0;
	return (result);
}
