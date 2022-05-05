#include "../includes/minishell.h"

static void	kernel_program(void)
{
	// можно вставить проверку первого pipe в строке и выходить если есть
	while (check_last_pipe(g_data.input))
		add_input();
	if (g_data.input && *g_data.input)
		add_history(g_data.input);
	if (check_open_quotes(g_data.input))
		return ;
	lexer();
	if (invalid_tokens(g_data.tokens))
		return ;
	parser();
	if (invalid_redirects(g_data.cmds))
		return ;
	executor(g_data.cmds);
}

static void	minishell_loop(void)
{
	while (1)
	{
		init_g_data();
		signal(SIGINT, sigint_handler_main);
		display_ctrl_c(ON);
		g_data.input = readline(PROMPT_MAIN);
		signal(SIGINT, SIG_IGN);
		display_ctrl_c(OFF);
		if (!g_data.input)
		{
			ft_putstr_fd(MESS_SIG_EOF, STDOUT_FILENO);
			end_program(NULL, 0, END1);
		}
		if (*g_data.input && ft_strcmp(g_data.input, "\n"))
			kernel_program();
		clear_data_loop();
	}
}

int	main(int argc, char **argv, char **envp)
{
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
		exit(warning(ERROR_NUM_ARGS, 1));
	(void)argv;
	g_data.envp = new_envp(envp);
	g_data.status = 0;
	minishell_loop();
	clear_g_data();
	return (0);
}
