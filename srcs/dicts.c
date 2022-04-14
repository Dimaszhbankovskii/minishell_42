#include "../includes/minishell.h"

t_dict	*new_dict(char *key, t_token *token)
{
	t_dict	*new;

	new = (t_dict *)malloc(sizeof(t_dict));
	if (!new)
		exit (1); // manage error
	new->key = ft_strdup(key);
	if (!new)
		exit (1); // manage error
	if (token && token->type != PIPE)
	{
		new->value = ft_strdup(token->content);
		if (!new)
			exit (1); // manage error
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

t_dict	*last_dict(t_dict *dict)
{
	t_dict	*tmp;

	tmp = dict;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_dict(t_dict **dict, t_dict *new)
{
	if (new)
	{
		if (!*dict)
			*dict = new;
		else
			last_dict(*dict)->next = new;
	}
}

