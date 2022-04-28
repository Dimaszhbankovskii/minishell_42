#include "../../includes/minishell.h"

t_arg	*new_arg(char *content)
{
	t_arg	*new;

	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
		end_program("Error\n", 1, END1);
	if (content)
	{
		new->value = ft_strdup(content);
		if (!new->value)
		{
			free (new);
			end_program("Error\n", 1, END1); //error
		}
	}
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

void	add_back_list_arg(t_arg **args, t_arg *new)
{
	t_arg	*tmp;

	if (new)
	{
		tmp = *args;
		if (!tmp)
			*args = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}
