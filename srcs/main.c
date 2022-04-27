#include "../includes/minishell.h"

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
	// check_errors
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
		// if (!ft_strcmp(g_data.input, "exit")) // ??? (будет команда обрабатываться)
		// 	break ;
		kernel_program();
	}
	clear_g_data();
	return (0);
}
