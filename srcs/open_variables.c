#include "../includes/minishell.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	len_envp_var(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*get_var(char *str)
{
	char	*var;
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	i++;
	var = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!var)
		exit (1); // error manager
	
}

char	*find_variable(char *src, int len)
{
	char	*name;
	char	**envp;
	int		i;

	name = (char *)malloc(sizeof(char) * (len + 1));
	if (!name)
		exit (1); // manage_error
	ft_strlcpy(name, src, len + 1);
	envp = g_data.envp;
	while (envp[i])
	{
		if (!ft_strncmp(name, envp[i], max(len, len_envp_var(envp[i]))))
		{
			free (name);
			name=get_var(envp[i]);
		}
			// нашли переменную, копируем ее
		i++;
	}
	if (ft_strcmp(name, "?"))
	{
		free (name);
		name = ft_itoa(g_data.status);
	}
}

char	*open_variable(char *content)
{
	char	*var_name;
	char	*out;
	int 	i;
	int		len;

	i = 0;
	len = 0;
	while (content[i] != '$')
		i++;
	i++;
	if (content[i] == '?' || ft_isdigit(content[i]))
	{
		len++;
		i++;
	}
	else
	{
		while (content[i] && (ft_isalnum(content[i]) || content[i] == '_'))
		{
			len++;
			i++;
		}
	}
	var_name = find_variable(content + i - len, len);
}
