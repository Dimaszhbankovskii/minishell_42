#include "../includes/minishell.h"

static char	*remove_outer_quotes(char *src)
{
	char	*dest;

	dest = (char *)malloc(sizeof(char) * ft_strlen(src) - 1);
	if (!dest)
		exit (1); // error malloc
	ft_strlcpy(dest, src + 1, ft_strlen(src) - 1);
	free (src);
	return (dest);
}

void	lexer_update_tokens(void)
{
	t_token	*tmp;

	tmp = g_data.tokens;
	while (tmp)
	{
		if (tmp->type == QUOTES || tmp->type == DQUOTES)
		{
			tmp->content = remove_outer_quotes(tmp->content);
		}
		// if (tmp->type == WORD || tmp->type == QUOTES)
		// 	open_variable(tmp->content); // раскрытие $
		tmp = tmp->next;
	}
}
