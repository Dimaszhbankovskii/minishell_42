#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_token
{
    char    		*content;
    struct s_token	*next;
}               t_token;

typedef struct s_main
{
    char    *input;
    t_token *tokens;
}               t_main;

t_main  g_data;

void    lexer(void);
void    lexer_update_tokens(void);

#endif