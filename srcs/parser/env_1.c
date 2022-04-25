#include "../../includes/minishell.h"

static char	*get_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	// if (str[i] == '=')
	// 	i++;
	if (str[i] != '=')
	{
		warning("bad env in start program\n", 1);
		return (NULL);
	}
	key = (char *)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, str, i + 1);
	return (key);
}

t_env	*new_elem_env(char *str)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = get_key(str);
	if (!new->key)
	{
		free (new);
		return (NULL);
	}
	new->value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!new->value)
	{
		free (new->key);
		free (new);
		return(NULL);
	}
	new->str = ft_strdup(str);
	if (!new->str)
	{
		free (new->key);
		free (new->value);
		free (new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_env	*last_elem_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_elem_env(t_env **env, t_env *new)
{
	if (new)
	{
		if (!*env)
			*env = new;
		else
			last_elem_env(*env)->next = new;
	}
}

t_env	*list_env(char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		new = new_elem_env(envp[i]);
		if (!new)
		{
			free_list_env(env);
			end_program(ERROR_INIT_LIST_ENV, 1, END1);
		}
		add_elem_env(&env, new);
		i++;
	}
	return (env);
}
