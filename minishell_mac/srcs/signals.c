#include "../includes/minishell.h"

void	sigint_handler_main(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	display_ctrl_c(int display)
{
	struct termios	t;

	tcgetattr(0, &t);
	if (display == OFF)
		t.c_lflag |= ECHOCTL;
	else
		t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	sigint_handler_child(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (signum == SIGQUIT)
		ft_putstr_fd(MESS_QUIT, STDOUT_FILENO);
	exit(130);
}
