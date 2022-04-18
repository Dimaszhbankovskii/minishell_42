#include "../includes/minishell.h"

void	error_mess(char *mess, int code)
{
	perror(mess);
	exit (code);
}
