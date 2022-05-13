#include "../../include/built_in.h"

void	env(char **envp)
{
	char	**i;

	i = envp;
	while (*i)
	{
		if (ft_strchr(*i, '='))
			printf("%s\n", *i);
		++i;
	}
}
