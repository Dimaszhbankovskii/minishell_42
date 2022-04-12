#include "../includes/minishell.h"

char	*ft_readline(void)
{
	char	*str;

	str = readline(">>");
	if (str)
		add_history(str);
	return (str);
}

void	init_g_data(void)
{
	g_data.input = NULL;
	g_data.tokens = NULL;
}

void	check_print(void)
{
	t_token	*tmp;

	tmp = g_data.tokens;
	printf("input:\n%s\n", g_data.input);
	if (!tmp)
		printf("NULL\n");
	while (tmp)
	{
		printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 1)
		exit (1); // error num args
	(void)argv;
	init_g_data();
	while (1)
	{
		g_data.input = ft_readline();
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
			break ;
		}
		lexer();
		check_print();
	}
	return (0);
}
