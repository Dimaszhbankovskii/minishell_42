#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h> // ubuntu header need to delete
# include "../libft/libft.h"

# define FT_WEXITSTATUS(x) ((x >> 8) & 0x000000ff)

# define END1 0
# define END2 1

# define SEPARATOR 1 // ' ', '\t'
# define WORD 2
# define QUOTES 3 // ''
# define DQUOTES 4 // ""
# define RDR_IN 5 // <
# define RDR_OUT 6 // >
# define RDR_SRC 7 // <<
# define RDR_APD 8 // >>
# define PIPE 9 // |

# define BUILTIN_ECHO 1
# define BUILTIN_PWD 2
# define BUILTIN_ENV 3
# define BUILTIN_UNSET 4

# define ERROR_NUM_ARGS "Error: num args in input minishell\n"
# define ERROR_MALLOC_ENVP "Error: malloc in envp\n"
# define ERROR_INIT_LIST_ENV "Error: init list env\n"
# define ERROR_G_PIPE "g_data.pipe"
# define ERROR_READLINE "Error: readline\n"
# define ERROR_INIT_TOKEN "Error: init token\n"
# define ERROR_OPEN_VAR "Error: open variable\n" // доработать
# define ERROR_OPEN_QUOTES "Error: malloc in open quotes\n"
# define ERROR_COMBINE_TOKEN "Error: malloc in combine token\n"
# define ERROR_MALLOC_CMD "Error: malloc cmd\n"
# define ERROR_ADD_ELEM_TWO_ARR "Error: malloc in add elem two arr\n"
# define ERROR_INIT_DICT "Error: init dict\n"
# define ERROR_INIT_ID_CMD "Error: malloc id cmd\n"
# define ERROR_CREATE_HEREDOC "heredoc tmpfile"
# define ERROR_INIT_PIPE_EXECUTOR "pipex.pipe"
# define ERROR_FORK "pipex.fork"

typedef struct s_pipex
{
	int		i;
	int		num;
	int		used_pipes;
	int		pipes[2][2];
	pid_t	pid;
}				t_pipex;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct s_dict
{
	int				key;
	char			*value;
	struct s_dict	*next;
}				t_dict;

typedef struct s_cmd
{
	char			*id;
	char			**args;
	int				count;
	t_dict			*infd;
	t_dict			*outfd;
	char			*tmpname;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*str;
	struct s_env	*next;
}				t_env;

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

t_env	*list_env(char **envp);
void	add_elem_env(t_env **env, t_env *new);
t_env	*last_elem_env(t_env *env);
t_env	*new_elem_env(char *str);
t_env	*free_list_env(t_env *env);

void	lexer(void);
void	lexer_update_tokens(void);
void	open_variable(t_token *token);

t_token	*new_token(char *str, int type, int *index);
void	add_token(t_token **tokens, t_token *new);
void	free_tokens(void);

void	parser(void);
void	init_id_cmd(void);

t_cmd	*new_cmd(void);
t_cmd	*last_cmd(t_cmd *cmds);
void	add_cmd(t_cmd **cmds, t_cmd *new);
void	free_cmd(void);

t_dict	*new_dict(int key, t_token *token);
t_dict	*last_dict(t_dict *dict);
void	add_dict(t_dict **dict, t_dict *new);
t_dict	*free_dict(t_dict *dict);
int		count_cmds(t_cmd *cmds);

void	executor(t_cmd *cmds);
void	handling_heredoc(t_cmd *cmds);
void	child_process(t_pipex *pipex, t_cmd *cmd);
void	redirect_input(t_cmd *cmd);
void	redirect_output(t_cmd *cmd);

void	execute_echo(t_cmd *cmd);
void	execute_pwd(void);
void 	execute_env(void);
void	execute_unset(t_env **env, char **args);

void	save_update_envp(void);
void	get_update_envp(void);

int		execute_binary(t_cmd *cmd);

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
void	check_print(void);

#endif