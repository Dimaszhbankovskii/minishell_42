#include "../includes/minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		exit (1); // manage error
	cmd->id = 0;
	cmd->args = NULL;
	cmd->count = 0;
	cmd->infd = NULL;
	cmd->outfd = NULL;
	cmd->tmpname = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*last_cmd(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_cmd(t_cmd **cmds, t_cmd *new)
{
	if (new)
	{
		if (!*cmds)
			*cmds = new;
		else
			last_cmd(*cmds)->next = new;
	}
}
