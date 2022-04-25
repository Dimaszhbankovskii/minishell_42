#include "../includes/minishell.h"

void	print_envp(void)
{
	char	**envp;
	int		i;

	envp = g_data.envp;
	i = 0;
	printf("------------------------------ g_data.envp -----------------------------\n");
	while (envp && envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	print_list_env(void)
{
	t_env	*env;

	env = g_data.env;
	printf("------------------------------ g_data.env ------------------------------\n");
	while (env)
	{
		printf("key  -->%s\n", env->key);
		printf("value-->%s\n", env->value);
		env = env->next;
	}
}

void	print_list_env_tmp(t_env *head)
{
	t_env	*env;

	env = head;
	printf("------------------------------ g_data.env ------------------------------\n");
	while (env)
	{
		printf("key  -->%s\n", env->key);
		printf("value-->%s\n", env->value);
		// printf("%s\n", env->str);
		env = env->next;
	}
}

void	print_tokens(void)
{
	t_token	*token;

	token = g_data.tokens;
	printf("------------------------------ g_data.token ----------------------------\n");
	if (!token)
		printf("g_data.token = NULL\n");
	while (token)
	{
		printf("type = %d \t {%s}\n", token->type, token->content);
		token = token->next;
	}
}

void	print_cmds(void)
{
	t_cmd	*cmd;
	int		i;
	t_dict	*tmp;

	cmd = g_data.cmds;
	printf("------------------------------ g_data.cmds -----------------------------\n");
	if (!cmd)
		printf("g_data.cmd = NULL\n");
	while (cmd)
	{
		printf("cmd %s:\n", cmd->id);
		printf("args: ");
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf("[%s], ", cmd->args[i]);
			i++;
		}
		printf("\n");
		if (cmd->infd)
		{
			tmp = cmd->infd;
			printf("infd: ");
			while (tmp)
			{
				printf("{'%d'; ", tmp->key);
				if (tmp->value)
					printf("'%s'} ", tmp->value);
				else
					printf("'NULL'} ");
				tmp = tmp->next;
			}
		}
		else
			printf("infd = NULL");
		printf("\n");
		if (cmd->outfd)
		{
			tmp = cmd->outfd;
			printf("outfd: ");
			while (tmp)
			{
				printf("{'%d'; ",tmp->key);
				if (tmp->value)
					printf("'%s'} ", tmp->value);
				else
					printf("'NULL'} ");
				tmp = tmp->next;
			}
		}
		else
			printf("outfd = NULL");
		printf("\n\n");
		cmd = cmd->next;
	}
}

void	check_print(void)
{
	printf("------------------------------------------------------------------------\n");
	print_envp();
	printf("\n------------------------------------------------------------------------\n");
	print_list_env();
	printf("\n------------------------------------------------------------------------\n");
	printf("input:\n%s\n", g_data.input);
	printf("\n------------------------------------------------------------------------\n");
	print_tokens();
	printf("\n------------------------------------------------------------------------\n");
	print_cmds();
}
