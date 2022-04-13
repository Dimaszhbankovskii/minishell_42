#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define SEPARATOR 1 // ' ', '\t'
# define WORD 2
# define QUOTES 3 // ''
# define DQUOTES 4 // ""
# define RDR_IN 5 // <
# define RDR_OUT 6 // >
# define RDR_SRC 7 // <<
# define RDR_APD 8 // >>
# define PIPE 9 // |

typedef struct s_token
{
    char    		*content;
    int             type;
    struct s_token	*next;
}               t_token;

typedef struct s_main
{
    char    *input;
    char    **envp;
    int     status;
    t_token *tokens;
}               t_main;

t_main  g_data;

void    lexer(void);
void    lexer_update_tokens(void);
char	*open_variable(char *content);

t_token	*new_token(char *str, int type, int *index);
void	add_token(t_token **tokens, t_token *new);


void	check_print(void);


#endif