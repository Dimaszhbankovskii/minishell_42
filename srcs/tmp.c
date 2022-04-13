// static int	check_open_quotes(int index)
// {
// 	int	i;

// 	i = 0;
// 	while (i < index)
// 	{
// 		if (g_data.input[i] == '"')
// 		{
// 			i++;
// 			while (i < index && g_data.input[i] != '"')
// 				i++;
// 			if (i == index)
// 				return (1);
// 		}
// 		if (g_data.input[i] == '\'')
// 		{
// 			i++;
// 			while (i < index && g_data.input[i] != '\'')
// 				i++;
// 			if (i == index)
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// static char	*str_token(int *index)
// {
// 	char	*content;
// 	char	*tmp;
// 	int		i;

// 	content = g_data.input + *index;
// 	tmp = (char *)malloc(sizeof(char) * (ft_strlen(content) + 1));
// 	if (!tmp)
// 		exit (1); // manage_error (error malloc token)
// 	i = 0;
// 	while (!ft_strchr(" <>|", content[i]) || check_open_quotes(*index + i))
// 	{
// 		tmp[i] = content[i];
// 		i++;
// 	}
// 	tmp[i] = '\0';
// 	return (tmp);
// }

// static char	*remove_quotes(char *src, char chr, int *index)
// {
// 	char	*dest;
// 	int		start;

// 	dest = (char *)malloc(sizeof(char) * (ft_strlen(src) - 1));
// 	if (!dest)
// 		exit (1); // error malloc
// 	start = *index;
// 	(*index)++;
// 	while (src[*index] != chr && src[*index])
// 		(*index)++;
// 	ft_strlcpy(dest, src, start + 1);
// 	ft_strlcpy(dest + start, src + start + 1, *index - start);
// 	ft_strlcpy(dest + *index - 1, src + *index + 1, ft_strlen(src) - *index);
// 	(*index)--;
// 	free (src);
// 	return (dest);
// }

// static void	update_token_content(t_token *token)
// {
// 	char	*content;
// 	int		i;

// 	content = token->content;
// 	i = 0;
// 	while (content && content[i])
// 	{
// 		if (content[i] == '"' || content[i] == '\'')
// 			content = remove_quotes(content, content[i], &i);
// 		else
// 			i++;
// 	}
// 	token->content = content;
// }
