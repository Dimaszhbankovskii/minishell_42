#include "../includes/minishell.h"

void	clear_g_data(void)
{
	if (g_data.input)
		free (g_data.input);
	if (g_data.tokens)
		free_tokens();
}
