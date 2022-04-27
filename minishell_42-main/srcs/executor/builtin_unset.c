#include "../../includes/minishell.h"

static int	check_valid_name(char *name)
{
	int	i;

	i = 0;
	while (name && name[i])
	{
		if (name[i])
		i++;
	}
}

char	**execute_unset(char **envp, char **args)
{
	int	i;
	int	j;
	int	k;

	if (!args[1])
		return (envp);
	i = 0;
	while (args && args[i++])
	{

	}
}
