#include "../includes/minishell.h"

char	*ft_readline(void)
{
	char	*str;

	str = readline(">>");
	if (str)
		add_history(str);
	return (str);
}

char	**new_envp(char **envp)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (envp && envp[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		exit (1); // manage error
	i = 0;
	while (envp && envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
			exit (1); // manage error
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	init_g_data(char **envp)
{
	g_data.envp = new_envp(envp);
	g_data.status = 0;
	g_data.input = NULL;
	g_data.tokens = NULL;
	g_data.cmds = NULL;
}

static void	kernel_program(void)
{
	lexer();
	parser();
	executor(g_data.cmds);
	
	clear_data_loop();
	// printf("--------------- check ----------------\n");
	// check_print(); // check
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		exit (1); // error num args
	(void)argv;
	init_g_data(envp);
	while (1)
	{
		g_data.input = ft_readline();
		// if (!g_data.input)  // ДЛЯ ТЕСТА LEAKS
		// 	g_data.input = ft_strdup("cat < file1 | cat > file_out"); // ДЛЯ ТЕСТА LEAKS
		if (!g_data.input)
			exit (0);
		if (!*g_data.input || !ft_strcmp(g_data.input, "\n"))
		{
			free (g_data.input);
			continue;
		}
		if (!ft_strcmp(g_data.input, "exit"))
		{
			free (g_data.input);
			g_data.input = NULL;
			break ;
		}
		kernel_program();
		// g_data.input = ft_strdup("exit"); // ДЛЯ ТЕСТА LEAKS
	}
	clear_g_data();
	return (0);
}
