#include "../../includes/minishell.h"

static void	init_pipex(t_pipex *pipex, t_cmd *cmds)
{
	pipex->i = 0;
	pipex->num = count_cmds(cmds);
	pipex->used_pipes = 0;
	pipex->pipes[0][0] = -1;
	pipex->pipes[0][1] = -1;
	pipex->pipes[1][0] = -1;
	pipex->pipes[1][1] = -1;
}

static void	wait_child_process(t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < pipex.num)
	{
		waitpid(-1, 0, 0);
		i++;
	}
}

static void	execute_cd_exit(t_cmd *cmd, int index)
{
	int	flag_execute;

	if (count_cmds(cmd) == 1 && !index)
		flag_execute = 1;
	else
		flag_execute = 0;
	if (!ft_strcmp(cmd->args[0], "exit"))
		execute_exit(cmd, flag_execute);
	// if (!ft_strcmp(cmd->args[0], "cd"))
	// 	execute_cd(cmd->args, flag_execute);
}

void sigint_handler_child(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("EXIT!!!\n",STDOUT_FILENO);
	else if (signum == SIGQUIT)
		ft_putstr_fd("QUITE EXIT!!!\n",STDOUT_FILENO);
	exit(130);
}

void	executor(t_cmd *cmds)
{
	t_pipex	pipex;
	t_cmd	*cmd;

	init_pipex(&pipex, cmds);
	handling_heredoc(cmds);
	cmd = cmds;
	while (pipex.i < pipex.num)
	{
		execute_cd_exit(cmd, pipex.i);
		if (pipe(pipex.pipes[pipex.used_pipes]) < 0)
			end_program(ERROR_INIT_PIPE_EXECUTOR, errno, END2);
		pipex.pid = fork();
		if (pipex.pid < 0)
			end_program(ERROR_FORK, errno, END2);
		if (!pipex.pid)
		{
			signal(SIGINT, sigint_handler_child);
			signal(SIGQUIT, sigint_handler_child);
			child_process(&pipex, cmd);
		}
		close(pipex.pipes[1- pipex.used_pipes][0]);
		close(pipex.pipes[pipex.used_pipes][1]);
		if (pipex.i == pipex.num - 1 && define_builtin(cmd))
			get_update_envp(); //обновление окружения
		pipex.used_pipes = 1 - pipex.used_pipes;
		pipex.i++;
		cmd = cmd->next;
	}
	close(pipex.pipes[1- pipex.used_pipes][0]);
	wait_child_process(pipex);
}
