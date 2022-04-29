#include "../includes/minishell.h"

static int check_quotes()
{
	int		i;
	char	quote;

	i=-1;
	while (g_data.input[++i])
	if (g_data.input[i] == '\"' || g_data.input[i] == '\'' )
	{
		quote = g_data.input[i++];
		while (g_data.input[i])
		{
			if (g_data.input[i] == quote)
			break ;
			i++;
		}
		if (!g_data.input[i])
		return (0);
	}
	return (1);
}

static int	check_pipes()
{
	int	i;

	//NULL input??
	i = ft_strlen(g_data.input) - 1;
	while(i >=0)
	{
	if (g_data.input[i] == ' ' || g_data.input[i] == '\t')
		i--;
	else if (g_data.input[i] == '|')
		return (0);
	else
		return (1);
	}
	return (1);
}

static void	add_input(void)
{
	char *new_input;
	char *line;

	line = readline(">");
	if (!line)
		exit(1); //MALLOC ERROR
	new_input = ft_strjoin(g_data.input, line);
	if (!new_input)
		exit(1);//HANDLE MALLOC ERROR
	free (g_data.input);
	g_data.input = new_input;
}

static int	print_fd_error(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",STDERR_FILENO);
	ft_putstr_fd(str,STDERR_FILENO);
	ft_putstr_fd("'\n",STDERR_FILENO);
	return (0);
}

static int check_dict(t_dict *dict)
{
	while (dict)
	{
	if (!dict->value)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",STDERR_FILENO);
		return (0);
	}
	if(!ft_strcmp(dict->value, "<<"))
		return (print_fd_error("<<"));
	if (!ft_strcmp(dict->value, ">>"))
		return (print_fd_error(">>"));
	if(ft_strcmp(dict->value, "<"))
		return (print_fd_error("<"));
	if(!ft_strcmp(dict->value, ">"))
		return (print_fd_error(">"));
	if(!ft_strcmp(dict->value, "|"))
		return (print_fd_error("|"));
	dict = dict->next;
	}
	return (1);
}

static int check_fd(void)
{
	t_cmd *cmd;

	cmd = g_data.cmds;
	while (cmd)
	{
	if (!check_dict(cmd->infd) || !check_dict(cmd->outfd))
		return (0);
	cmd = cmd->next;
	}
	return (1);
}

static void	kernel_program(void)
{
	while (!check_pipes())
		add_input();
	if (g_data.input && *g_data.input)
		add_history(g_data.input);
	if (check_quotes())
	{
		lexer();
		// Проверка слияния 2х pipe | (|| или | |)
		parser();
		if (check_fd())
			executor(g_data.cmds);
		// Валидность редиректов (<< >> < >)
		// check_print(); // check
	}
	clear_data_loop();
}

static void	minishell_loop(void)
{
	while (1)
	{
		init_g_data();
		signal(SIGINT, sigint_handler_main);
		display_ctrl_c(ON);
		g_data.input = readline(">>");
		signal(SIGINT, SIG_IGN);
		display_ctrl_c(OFF);
		if (!g_data.input) // ошибка readline
		{
			write(1, ">> exit\n", 8);
			end_program(NULL, 0, END1);
		}
		if (!*g_data.input || !ft_strcmp(g_data.input, "\n")) // ???
		{
			free (g_data.input);
			continue;
		}
		kernel_program();
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
