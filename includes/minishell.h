#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
// # include <readline/r>
# include <fcntl.h>
# include <sys/wait.h> // ubuntu header need to delete
# include "../libft/libft.h"
# include "parser.h"
# include "executor.h"
# include "errors.h"

# define FT_WEXITSTATUS(x) ((x >> 8) & 0x000000ff)

# define END1 0
# define END2 1

# define ON 0
# define OFF 1

typedef struct s_main
{
	int		fd[3][2]; // 0 - char *envp, 1 - count, 2 - status
	int		status;
	char	**envp;
	t_env	*env;
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;
}				t_main;

t_main	g_data;

char	**new_envp(char **envp);
void	init_g_data(void);




void	end_program(char *mess, int code, int mode);

void	clear_data_loop(void);
void	clear_g_data(void);

int		max(int a, int b);
char	**malloc_two_array_char(int len);
void	free_two_array_char(char **array);
void	add_back_elem_two_array_char(char **array, char *elem, int len);
char	*find_str(char **array, char *str);
int		size_two_array_char(char **array);

void	error_mess(char *mess, int code);
int		warning(char *mess, int code);

// delete
void	print_list_env(void);
void	print_list_env_tmp(t_env *head);
void	check_print(void);

#endif