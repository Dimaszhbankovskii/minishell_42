#include "../includes/minishell.h"

char	*ft_readline(void)
{
	char	*str;

	str = readline(">>");
	if (str)
		add_history(str);
	return (str);
}

int	main(int argc, char **argv)
{
	char	*cmd;

	(void)argc;
	(void)argv;
	while (1)
	{
		cmd = ft_readline();
		if (!cmd)
			exit (0);
		if (!*cmd || !ft_strcmp(cmd, "\n"))
		{
			free (cmd);
			continue;
		}
		if (!ft_strcmp(cmd, "exit"))
		{
			free (cmd);
			break ;
		}
		write(1, cmd, ft_strlen(cmd));
		write(1, "\n", 1);
		free (cmd);
	}
	return (0);
}
