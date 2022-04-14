#include "../includes/minishell.h"

char	**malloc_two_array_char(int len)
{
	char	**array;
	int	i;

	array = (char **)malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (i <= len)
		array[i++] = NULL;
	return (array);
}

void	add_elem_two_array(char **array, char *elem, int len)
{
	int	i;

	i = 0;
	while (array && i < len && array[i])
		i++;
	if (i < len)
		array[i] = ft_strdup(elem);
	if (!array[i])
		exit (1); // manager error
}

static void	init_cmd(t_token *token)
{
	t_token	*tmp;
	t_cmd	*cmd;

	tmp = token;
	if (tmp->type != PIPE)
	{
		add_cmd(&g_data.cmds, new_cmd());
		cmd = last_cmd(g_data.cmds);
		while (tmp && tmp->type != PIPE)
		{
			if (tmp->type == WORD || tmp->type == QUOTES || tmp->type == DQUOTES)
				cmd->count++;
			tmp = tmp->next;
		}
		cmd->args = malloc_two_array_char(cmd->count);
		if (!cmd->args)
			exit (1); // manager error
	}
}

void	cmd_get_args(char *arg)
{
	t_cmd	*cmd;

	cmd = last_cmd(g_data.cmds);
	add_elem_two_array(cmd->args, arg, cmd->count);
}

t_token	*find_token_path_redirect(t_token *token)
{
	t_token *tmp;

	tmp = token->next;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == SEPARATOR)
			tmp = tmp->next;
		else
			return (tmp);
	}
	return (tmp);
}

t_token	*cmd_get_redirect(t_token *token)
{
	t_token	*tmp;

	tmp = find_token_path_redirect(token);
	if (token->type == RDR_IN)
		add_dict(&last_cmd(g_data.cmds)->infd, new_dict("<", tmp)); //
	else if (token->type == RDR_OUT)
		add_dict(&last_cmd(g_data.cmds)->outfd, new_dict(">", tmp)); //
	else if (token->type == RDR_SRC)
		add_dict(&last_cmd(g_data.cmds)->infd, new_dict("<<", tmp)); //
	else if (token->type == RDR_APD)
		add_dict(&last_cmd(g_data.cmds)->outfd, new_dict(">>", tmp)); //
	return (tmp);
}

void	parser(void)
{
	t_token	*token;
	t_cmd	*cmd;
	int		i, j; //
	t_dict	*tmp; //

	token = g_data.tokens;
	cmd = g_data.cmds;
	while (token)
	{
		init_cmd(token);
		while (token && token->type != PIPE)
		{
			if (token && (token->type == WORD || token->type == QUOTES || \
			token->type == DQUOTES))
				cmd_get_args(token->content);
			if (token && (token->type == RDR_IN || token->type == RDR_OUT \
			|| token->type == RDR_SRC || token->type == RDR_APD))
				token = cmd_get_redirect(token);
			if (token && token->type != PIPE)
				token = token->next;
		}
		if (token)
			token = token->next;
	}

	printf("--------- check ----------\n");

	cmd = g_data.cmds;
	j = 1;
	while (cmd)
	{
		printf("cmd %d:\n", j);
		i = 0;
		printf("args: ");
		while (cmd->args && cmd->args[i])
		{
			printf("[%s], ", cmd->args[i]);
			i++;
		}
		
		if (cmd->infd)
		{
			tmp = cmd->infd;
			printf("\ninfd: ");
			while (tmp)
			{
				printf("{'%s'; '%s'} ", tmp->key, tmp->value);
				tmp = tmp->next;
			}
		}
		if (cmd->outfd)
		{
			tmp = cmd->outfd;
			printf("\noutfd: ");
			while (tmp)
			{
				printf("{'%s'; ", tmp->key);
				if (tmp->value)
					printf("'%s'} ", tmp->value);
				else
					printf("'NULL'} ");
				tmp = tmp->next;
			}
		}

		printf("\n--------------------------\n");
		cmd = cmd->next;
		j++;
	}
	// printf("i = %d\n", i);

	printf("--------------------------\n");

}
