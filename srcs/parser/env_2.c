#include "../../includes/minishell.h"

t_env	*free_list_env(t_env *env)
{
	t_env	*tmp;
	t_env	*del;

	del = env;
	while (del)
	{
		tmp = del->next;
		if (del->key)
			free (del->key);
		if (del->value)
			free (del->value);
		if (del->str)
			free (del->str);
		free(del);
		del = tmp;
	}
	return (NULL);
}
