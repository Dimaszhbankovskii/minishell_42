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

void sigint_handler_main()
{
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	display_ctrl_c(int display)
{
	struct termios t;

	tcgetattr(0, &t);
	if (display == OFF)
		t.c_lflag |= ECHOCTL;
	else
		t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}


int	main(int argc, char **argv, char **envp)
{
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
		exit(warning(ERROR_NUM_ARGS, 1));
	(void)argv;
	g_data.envp = new_envp(envp);
	g_data.status = 0;
	while (1)
	{
		init_g_data();
		signal(SIGINT, sigint_handler_main);
		display_ctrl_c(ON);
		g_data.input = ft_readline();
		signal(SIGINT, SIG_IGN);
		display_ctrl_c(OFF);
		if (!g_data.input) // ошибка readline
		{
			write(1, ">> exit\n", 8);
			end_program(NULL , 0, END1);
		}
		if (!*g_data.input || !ft_strcmp(g_data.input, "\n")) // ???
		{
			free (g_data.input);
			continue;
		}
		kernel_program();
	}
	clear_g_data();
	return (0);
}
