#include "../includes/minishell.h"

void	init_id_cmd(void)
{
	t_cmd	*tmp;
	int		id;

	id = 1;
	tmp = g_data.cmds;
	while (tmp)
	{
		tmp->id = id;
		id++;
		tmp = tmp->next;
	}
}
