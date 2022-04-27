#include "../../includes/minishell.h"

void	init_pipex(t_pipex *pipex, t_cmd *cmds)
{
	pipex->i = 0;
	pipex->num = count_cmds(cmds);
	pipex->used_pipes = 0;
	pipex->pipes[0][0] = -1;
	pipex->pipes[0][1] = -1;
	pipex->pipes[1][0] = -1;
	pipex->pipes[1][1] = -1;
}

void	wait_child_process(t_pipex pipex)
{
	int	i;

	i = 0;
	while (i < pipex.num)
	{
		waitpid(-1, 0, 0);
		i++;
	}
}

void sigint_handler_child()
{
	ft_putstr_fd("\n",STDOUT_FILENO);
	exit(130);
}

void	executor(t_cmd *cmds)
{
	t_pipex	pipex;

	t_cmd	*cmd;
	 pid_t pid[pipex.num];

	init_pipex(&pipex, cmds);
	handling_heredoc(cmds);
	cmd = cmds;
	while (pipex.i < pipex.num)
	{
		if (pipe(pipex.pipes[pipex.used_pipes]) < 0)
			exit(1); // error manager
		pid[pipex.i] = fork();
		if (pid[pipex.i] < 0)
			exit(1);
		if (!pid[pipex.i]) {
			signal(SIGINT, sigint_handler_child);
			child_process(&pipex, cmd);
		}
		close(pipex.pipes[1- pipex.used_pipes][0]);
		close(pipex.pipes[pipex.used_pipes][1]);
		pipex.used_pipes = 1 - pipex.used_pipes;
		pipex.i++;
		cmd = cmd->next;
		// update_envp(); обновление окружения
	}
	wait_child_process(pipex);
}
