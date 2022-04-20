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

void	child_process(t_pipex *pipex, t_cmd *cmd)
{
	// char	*tmp_cmd[] = {"/bin/cat", NULL};
	pid_t	child_bin;

	define_input_output(pipex, cmd); // перенаправление вводов и выводов
	
	// попытка выполнить builtin

	// либо бинарник системы или свой
	child_bin = fork();
	if (!child_bin)
		child_process_bin(pipex, cmd);
	waitpid(-1, NULL, 0);
	// execve(tmp_cmd[0], tmp_cmd, g_data.envp);	// execute_cmd();
	
	// save_envp();
}
