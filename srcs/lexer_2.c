#include "../includes/minishell.h"

static char	*remove_quotes(char *src, char chr, int *index)
{
	char	*dest;
	int		start;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) - 1));
	if (!dest)
		exit (1); // error malloc
	start = *index;
	(*index)++;
	while (src[*index] != chr && src[*index])
		(*index)++;
	ft_strlcpy(dest, src, start + 1);
	ft_strlcpy(dest + start, src + start + 1, *index - start);
	ft_strlcpy(dest + *index - 1, src + *index + 1, ft_strlen(src) - *index);
	(*index)--;
	free (src);
	return (dest);
}

static void	update_token_content(t_token *token)
{
	char	*content;
	int		i;

	content = token->content;
	i = 0;
	while (content && content[i])
	{
		if (content[i] == '"' || content[i] == '\'')
			content = remove_quotes(content, content[i], &i);
		else
			i++;
	}
	token->content = content;
}

void	lexer_update_tokens(void)
{
	t_token	*tmp;

	tmp = g_data.tokens;
	while (tmp)
	{
		update_token_content(tmp);
		tmp = tmp->next;
	}
}