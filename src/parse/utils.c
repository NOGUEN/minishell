/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: noguen <marvin@42.fr>					  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/05/12 18:55:21 by noguen			#+#	#+#			 */
/*   Updated: 2022/05/13 13:33:45 by noguen           ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

char	*cut_string(char **str)
{
	char	*ret;
	char	*tmp;
	int		size;
	int		i;

	ret = NULL;
	size = 0;
	tmp = *str;
	while (*tmp)
	{
		if (*tmp == ' ')
			break ;
		else if (*tmp == '\"' || *tmp == '\'')
			break ;
		else
			++size;
		++(tmp);
	}
	ret = (char *)malloc(sizeof(char) * (size + 1));
	ft_strlcpy(ret, *str, size + 1);
	i = -1;
	while (++i < size)
		++(*str);
	return (ret);
}

char	**copy_envp(char **envp)
{
	int		num_env;
	char	**copied;
	int		i;

	num_env = -1;
	while (envp[++num_env])
		;
	copied = malloc((num_env + 1) * sizeof(char *));
	copied[num_env] = NULL;
	i = -1;
	while (++i < num_env)
		copied[i] = ft_strdup(envp[i]);
	return (copied);
}

void	free_copied_env(char **copied)
{
	char	**i;

	i = copied;
	while (*i)
	{
		free(*i);
		++i;
	}
	free(copied);
}

char	**sort_env(char **envp)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;

	i = -1;
	j = 0;
	new = copy_envp(envp);
	while (new[++i])
	{
		j = i;
		while (new[++j])
		{
			if (ft_strncmp(new[i], new[j], ft_strlen(new[i])) > 0)
			{
				tmp = new[i];
				new[i] = new[j];
				new[j] = tmp;
			}
		}
	}
	return (new);
}

void	print_str_fd(char *s, int fd)
{
	if (fd < 0 || !(s))
		return ;
	write(fd, s, ft_strlen(s));
}
