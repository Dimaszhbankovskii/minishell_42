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

void	executor(t_cmd *cmds)
{
	t_pipex	pipex;
	t_cmd	*cmd;

	init_inf(&pipex, cmds);
	handling_heredoc(cmds);
	cmd = cmds;
	while (pipex.i < pipex.num)
	{
		if (pipe(pipex.pipes[pipex.used_pipes]) < 0)
			exit(1); // error manager
		
		// fork ()
		child_process(&pipex, cmd);
		// родитель ждем и отлавливает сигналы
		// обработка ошибок
		// потомок пошел на испольнение

		// обновление окружения глобалки
		pipex.i++;
	}
}
