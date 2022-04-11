#include "../includes/minishell.h"

void	unget_char(t_source *src)
{
	if (src->index < 0)
		return ;
	src->index--;
}

char	next_char(t_source *src)
{
	char	*chr;

	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	chr = 0;
	if (src->index == INIT_SRC_POS)
		src->index = -1;
	else
		chr = src->buffer[src->index];
	if (++src->index >= src->len)
	{
		src->index = src->len;
		return (EOF);
	}
	return (src->buffer[src->index]);
}

char	peek_char(t_source *src)
{
	long	position;

	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	position = src->index;
	if (position == INIT_SRC_POS)
		position++;
	if (position >= src->len)
		return (EOF);
	return (src->buffer[position]);
}

void	skip_white_spaces(t_source *src)
{
	char	chr;

	if (!src || !src->buffer)
		return ;
	while (((chr = peek_char(src)) != EOF) && (chr != ' ' || chr != '\t'))
		next_char(src);
}
