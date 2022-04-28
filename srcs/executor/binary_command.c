#include "../../includes/minishell.h"

// char	*relative_path(char *cmd)
// {
// 	char	*tmp1;
// 	char	*tmp2;

// 	tmp1 = getcwd(NULL, 0);
// 	if (!tmp1)
// 		end_program("Check relative path", errno, END2);
// 	tmp2 = ft_strjoin(tmp1, "/");
// 	free (tmp1);
// 	if (!tmp2)
// 		end_program("Error: malloc\n", 1, END1);
// 	tmp1 = ft_strjoin(tmp2, cmd);
// 	free (tmp2);
// 	if (!tmp1)
// 		end_program("Error: malloc\n", 1, END1);
// 	if (!access(tmp1, X_OK))
// 		return (tmp1);
// 	free (tmp1);
// 	return (NULL);
// }

// char	*absolute_path(char *cmd, char *relative)
// {

// }

static char	*search_paths(char **paths, char *cmd)
{
	// char	*relative;
	// char	*absolute;

	int		i;
	char	*tmp;
	char	*filename;

	// relative = relative_path(cmd);
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		filename = ft_strjoin(tmp, cmd);
		if (!filename)
		{
			free (tmp);
			return (NULL);
		}
		free (tmp);
		if (!access(filename, X_OK))
			return (filename);
		free(filename);
		i++;
	}
	return (NULL);
}

static char	**parsing_paths(char **envp)
{
	char	*tmp1;
	char	*tmp2;
	char	**paths;

	tmp1 = find_str(envp, "PATH=");
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strdup(tmp1 + ft_strlen("PATH="));
	if (!tmp2)
		return (NULL);
	paths = ft_split(tmp2, ':');
	if (!paths)
	{
		free(tmp2);
		return (NULL);
	}
	free (tmp2);
	return (paths);
}

static void	child_process_binary(t_cmd *cmd, char **envp)
{
	char	**paths_envp;
	char	*path_cmd;

	paths_envp = parsing_paths(envp);
	if (!paths_envp)
		exit(warning("Error: parsing ENVP PATH\n", EXIT_FAILURE));
	if (!cmd->args[0]) // check ( |   ls -l) (ls -l |    ) два случая надо ограничить
		exit(warning("Error: binary file not exist\n", EXIT_FAILURE)); // ???
	path_cmd = search_paths(paths_envp, cmd->args[0]);
	if (!path_cmd)
	{
		free_two_array_char(paths_envp);
		exit(warning("Error: binary file not exist\n", 127));
	}
	execve(path_cmd, cmd->args, g_data.envp);
	free_two_array_char(paths_envp);
	free (path_cmd);
	error_mess("execve", errno);
}

int	execute_binary(t_cmd *cmd)
{
	pid_t	child;

	child = fork();
	if (child < 0)
		return (warning("Error: fork\n", 1)); // error
	if (!child)
		child_process_binary(cmd, g_data.envp);
	else
		waitpid(child, &g_data.status, 0);
	// сделать макрос
	return (0);
}
