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
	define_input_output(pipex, cmd); // перенаправление вводов и выводов
	
	// if (есть builtin)
		// execute_builtin();
	// ARG=asdasdas
	//else
	execute_binary(cmd);
	// if (execute_binary(cmd))
		// warning("Error: fork in execute binary\n", 1);
	// printf("--------------check-------------------\n");
	// save_envp
	exit (0);
}
