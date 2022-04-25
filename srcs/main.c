#include "../includes/minishell.h"

char	**new_envp(char **envp)
{
	char	**new_envp;
	int		i;

	new_envp = malloc_two_array_char(size_two_array_char(envp));
	if (!new_envp)
		exit(warning(ERROR_MALLOC_ENVP, 1));
	i = 0;
	while (envp && envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			free_two_array_char(new_envp);
			exit(warning(ERROR_MALLOC_ENVP, 1));
		}
		i++;
	}
	return (new_envp);
}

void	init_g_data(void)
{
	g_data.env = NULL;
	g_data.input = NULL;
	g_data.tokens = NULL;
	g_data.cmds = NULL;
	g_data.env = list_env(g_data.envp);
	if (pipe(g_data.fd[0]) < 0)
		end_program(ERROR_G_PIPE, errno, END2);
	if (pipe(g_data.fd[1]) < 0)
		end_program(ERROR_G_PIPE, errno, END2);
	if (pipe(g_data.fd[2]) < 0)
		end_program(ERROR_G_PIPE, errno, END2);
}

char	*ft_readline(void)
{
	char	*str;

	str = readline(">>");
	if (str)
		add_history(str);
	return (str);
}

static void	kernel_program(void)
{	
	lexer();
	parser();
	executor(g_data.cmds);	
	// check_print(); // check
	clear_data_loop();
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		exit(warning(ERROR_NUM_ARGS, 1));
	(void)argv;
	g_data.envp = new_envp(envp);
	g_data.status = 0;
	while (1)
	{
		init_g_data();
		g_data.input = ft_readline();
		if (!g_data.input) // ошибка readline
			end_program(ERROR_READLINE, 1, END1);
		if (!*g_data.input || !ft_strcmp(g_data.input, "\n")) // ???
		{
			free (g_data.input);
			continue;
		}
		if (!ft_strcmp(g_data.input, "exit")) // ??? (будет команда обрабатываться)
			break ;
		kernel_program();
	}
	clear_g_data();
	return (0);
}
