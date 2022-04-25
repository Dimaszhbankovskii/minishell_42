#include "../../includes/minishell.h"

static void	define_input_output(t_pipex *pipex, t_cmd *cmd)
{
	if (!cmd->infd && pipex->i > 0)
	{
		dup2(pipex->pipes[1 - pipex->used_pipes][0], STDIN_FILENO);
		close(pipex->pipes[1 - pipex->used_pipes][0]);
	}
	else
		redirect_input(cmd);
	if (!cmd->outfd && pipex->i < pipex->num - 1)
	{
		dup2(pipex->pipes[pipex->used_pipes][1], STDOUT_FILENO);
		close(pipex->pipes[pipex->used_pipes][0]);
		close(pipex->pipes[pipex->used_pipes][1]);
	}
	else
		redirect_output(cmd);
}

static void	execute_builtin(t_cmd *cmd, int type_builtin)
{
	if (type_builtin == BUILTIN_ECHO)
		execute_echo(cmd);
	else if (type_builtin == BUILTIN_PWD)
		execute_pwd();
	else if (type_builtin == BUILTIN_ENV)
		execute_env();
	else if (type_builtin == BUILTIN_UNSET)
		execute_unset(&g_data.env, cmd->args);
	else if (type_builtin == BUILTIN_EXPORT)
		execute_export(g_data.envp, g_data.env, cmd->args);
}

static int	define_builtin(t_cmd *cmd)
{
	if (cmd->args)
	{
		if (!ft_strcmp(cmd->args[0], "echo"))
			return (BUILTIN_ECHO);
		else if (!ft_strcmp(cmd->args[0], "pwd"))
			return (BUILTIN_PWD);
		else if (!ft_strcmp(cmd->args[0], "env"))
			return (BUILTIN_ENV);
		else if (!ft_strcmp(cmd->args[0], "unset"))
			return (BUILTIN_UNSET);
		else if (!ft_strcmp(cmd->args[0], "export"))
			return (BUILTIN_EXPORT);
	}
	return (0);
}

void	child_process(t_pipex *pipex, t_cmd *cmd)
{
	int	type_builtin;

	define_input_output(pipex, cmd); // сделать обработку ошибок
	// перевести в нижний регистр название команды (если требуется)
	type_builtin = define_builtin(cmd);
	if (type_builtin)
		execute_builtin(cmd, type_builtin);
	// else if (check_tmp_vatiable(cmd)) // ARG=text, ARG1=text1
	// 	save_tmp_variable(cmd);
	else
		execute_binary(cmd);
	save_update_envp();
	close(pipex->pipes[1- pipex->used_pipes][0]);
	close(pipex->pipes[pipex->used_pipes][1]);
	exit (0);
}
