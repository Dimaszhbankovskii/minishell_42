#include "../../includes/minishell.h"

void	execute_echo(t_cmd *cmd)
{
	int	i;

	g_data.status = 0;
	if(!cmd->args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	i = 1;
	while (cmd->args[i] && *cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
		i++;
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!*cmd->args[1] || ft_strcmp(cmd->args[1], "-n"))
		ft_putchar_fd('\n', STDOUT_FILENO);
}

// void	execute_echo(t_cmd *cmd)
// {
// 	t_arg	*tmp;

// 	g_data.status = 0;
// 	if(!cmd->l_arg->next)
// 	{
// 		write(STDOUT_FILENO, "\n", 1);
// 		return ;
// 	}
// 	tmp = cmd->l_arg->next;
// 	while (cmd->args[i] && *cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
// 		i++;
// 	while (cmd->args[i])
// 	{
// 		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
// 		if (cmd->args[i + 1])
// 			ft_putchar_fd(' ', STDOUT_FILENO);
// 		i++;
// 	}
// 	if (!*cmd->args[1] || ft_strcmp(cmd->args[1], "-n"))
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// }

void	execute_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		exit(1); // malloc error
	ft_putstr_fd(path, STDOUT_FILENO);
	write(STDOUT_FILENO,"\n",1);
	free (path);
	g_data.status = 0;
}

void execute_env(void)
{
	int	i;

	i = 0;
	while(g_data.envp && g_data.envp[i])
	{
		ft_putstr_fd(g_data.envp[i++], STDOUT_FILENO);
		ft_putchar_fd('\n',STDOUT_FILENO);
	}
	g_data.status = 0;
}

void  execute_exit(t_cmd *cmd, int flag)
{
	if (!flag)
		return ;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd->args[1])
		{
			if (!ft_is_num(cmd->args[1]))
			{
				ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
				ft_putstr_fd(cmd->args[1], STDERR_FILENO);
				ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
				end_program(NULL, 255, END1);
			}
			else if (cmd->args[2])
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
				g_data.status = 1;
				return ;
			}
		end_program(NULL, ft_atoi(cmd->args[1]), END1);
		}
	end_program(NULL, 0, END1);
}
