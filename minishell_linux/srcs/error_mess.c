#include "../includes/minishell.h"

void	error_mess(char *mess, int code)
{
	perror(mess);
	exit (code);
}

int	warning(char *mess, int code)
{
	ft_putstr_fd(mess, STDERR_FILENO);
	return (code);
}
