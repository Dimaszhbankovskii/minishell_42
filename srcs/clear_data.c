#include "../includes/minishell.h"

void	end_program(char *mess, int code, int mode)
{
	clear_g_data();
	if (mode == END1 && mess)
		write(STDERR_FILENO, mess, ft_strlen(mess));
	else if (mode == END2)
		perror(mess);
	exit (code);
}

// очистка в цикле (на следующую итерацию)
void	clear_data_loop(void)
{
	if (g_data.env)
		free_list_env(g_data.env);
	if (g_data.input)
		free (g_data.input);
	if (g_data.tokens)
		free_tokens();
	if (g_data.cmds)
		free_cmd();
}

// очистка в конце программы
// очистка при ошибках
void	clear_g_data(void)
{
	if (g_data.envp)
		free_two_array_char(g_data.envp);
	if (g_data.env)
		g_data.env = free_list_env(g_data.env);
	if (g_data.input)
		free (g_data.input);
	if (g_data.tokens)
		free_tokens();
	if (g_data.cmds)
		free_cmd();
}
