#include "../../includes/minishell.h"

void	init_id_cmd(void)
{
	t_cmd	*tmp;
	int		id;

	id = 1;
	tmp = g_data.cmds;
	while (tmp)
	{
		tmp->id = ft_itoa(id);
		if (!tmp->id)
			end_program(ERROR_INIT_ID_CMD, 1, END1);
		id++;
		tmp = tmp->next;
	}
}
