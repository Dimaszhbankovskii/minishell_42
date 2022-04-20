#include "../../includes/minishell.h"

static char	*search_paths(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*filename;
	char *path;


	//absolute path
	if (!access(cmd, X_OK)) {
		//printf("%s\n",cmd);
		return (ft_strdup(cmd));
	}


	//relative path
	path= getcwd(NULL, 0);
	if (!path)
		exit(1); // malloc error
	filename = ft_strjoin(path, cmd);
	if (!access(filename, X_OK)) {
		//printf("%s\n",filename);
		return (filename);
	}


	//envp path
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			exit(1);
		filename = ft_strjoin(tmp, cmd);
		if (!filename)
		{
			free (tmp);
			exit(1);
		}
		free(tmp);
		if (!access(filename, X_OK)) {
			//printf("%s\n",filename);
			return (filename);
		}
		i++;
		free(filename);
	}
	return (NULL);
}

static char	**find_str(char **array, char *str)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		if (!ft_strncmp(array[i], str, ft_strlen(str)))
			return (&array[i]);
		i++;
	}
	return (NULL);
}

static char	**parsing_paths(void)
{
	char	*tmp1;
	char	*tmp2;
	char	**paths;

	tmp1 = *find_str(g_data.envp, "PATH=");
	if (!tmp1)
		exit(1);
	tmp2 = ft_strdup(tmp1 + ft_strlen("PATH="));
	if (!tmp2)
		exit(1);
	paths = ft_split(tmp2, ':');
	if (!paths)
	{
		free(tmp2);
		exit(1);
	}
	free (tmp2);
	return (paths);
}

void child_process_bin(t_pipex *pipex, t_cmd *cmd)
{
	char	*path_cmd;
	char	**path_envp;
	
	(void)pipex;
	path_envp = parsing_paths();
	path_cmd = search_paths(path_envp, cmd->args[0]);
	if (!path_cmd)
	{
		printf("no cmd\n");
		exit(1);
	}
	execve(path_cmd, cmd->args, g_data.envp);
	printf("no execve cmd\n");
	exit (1);
}
