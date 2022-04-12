#include "../includes/minishell.h"

static t_token	*new_token(char *str, int *index)
{
	t_token	*token;

	if (!str)
		exit (1); // manage_error (error malloc ft_strdup)
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit (1); // manage_error (error malloc token)
	token->content = str;
	token->next = NULL;
	*index = *index + ft_strlen(str) - 1;
	return (token);
}

static void	add_back_token(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (new)
	{
		tmp = *tokens;
		if (!tmp)
			*tokens = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

static int	check_open_quotes(int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (g_data.input[i] == '"')
		{
			i++;
			while (i < index && g_data.input[i] != '"')
				i++;
			if (i == index)
				return (1);
		}
		if (g_data.input[i] == '\'')
		{
			i++;
			while (i < index && g_data.input[i] != '\'')
				i++;
			if (i == index)
				return (1);
		}
		i++;
	}
	return (0);
}

static char	*str_token(int *index)
{
	char	*content;
	char	*tmp;
	int		i;

	content = g_data.input + *index;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(content) + 1));
	if (!tmp)
		exit (1); // manage_error (error malloc token)
	i = 0;
	while (!ft_strchr(" <>|", content[i]) || check_open_quotes(*index + i))
	{
		tmp[i] = content[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	lexer(void)
{
	int		i;

	i = 0;
	while (*(g_data.input + i))
	{
		while (*(g_data.input + i) == ' ')
			i++;
		if (!ft_strncmp(g_data.input + i, "<<", 2))
			add_back_token(&g_data.tokens, new_token(ft_strdup("<<"), &i));
		else if (!ft_strncmp(g_data.input + i, ">>", 2))
			add_back_token(&g_data.tokens, new_token(ft_strdup(">>"), &i));
		else if (!ft_strncmp(g_data.input + i, "<", 1))
			add_back_token(&g_data.tokens, new_token(ft_strdup("<"), &i));
		else if (!ft_strncmp(g_data.input + i, ">", 1))
			add_back_token(&g_data.tokens, new_token(ft_strdup(">"), &i));
		else if (!ft_strncmp(g_data.input + i, "|", 1))
			add_back_token(&g_data.tokens, new_token(ft_strdup("|"), &i));
		else
			add_back_token(&g_data.tokens, new_token(str_token(&i), &i));
		i++;
	}
	lexer_update_tokens();
}
