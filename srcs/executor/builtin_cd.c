#include "../../includes/minishell.h"

char	**cd_pwd_oldpwd(char *old_path)
{
	char	*pwd;
	char	cwd[4096];
	char	*new_old_path;

	new_old_path = ft_strjoin("OLDPWD=", old_path); // a
	free(old_path);
	pwd = ft_strjoin("PWD=", getcwd(cwd, 4096));
	g_line.envp = replace_envp_el(g_line.envp, pwd, "PWD=");
	if (check_unset("OLDPWD=", g_line.envp))
		g_line.envp = replace_envp_el(g_line.envp, new_old_path, "OLDPWD=");
	else
		g_line.envp = export_envp(g_line.envp, new_old_path, 1);
	free(new_old_path);
	free(pwd);
	return (g_line.envp);
}

cd

void	cd_update_env(char *old_path)
{
	char	cwd[4096];
	char	*var;
	char	*pwd;
	t_env	*tmp;

	var = ft_strjoin("OLDPWD=", old_path);
	tmp = find_elem_env(&g_data.env, "OLDPWD");
	if (tmp) // если в окружение env есть OLDPWD обновляем
	{
		free(tmp->value);
		tmp->value = old_path;
		free(tmp->str);
		tmp->str = var;
	}
	else // если нет, создаем и добавляем
	{
		tmp = new_elem_env(var);
		if (!tmp)
			end_program("Error malloc\n", 1, END1);
		add_elem_env(&g_data.env, tmp);
	}
	pwd = ft_strdup(getcwd(cwd, 4096));
	var = ft_strjoin("OLDPWD=", old_path);
	if (!pwd)
		exit (1); //error
	tmp = find_elem_env(&g_data.env, "PWD");
	if (tmp) // если в окружение env есть OLDPWD обновляем
	{
		free(tmp->value);
		tmp->value = pwd;
		free(tmp->str);
		tmp->str = var;
	}
	else // если нет, создаем и добавляем
	{
		tmp = new_elem_env(var);
		if (!tmp)
			end_program("Error malloc\n", 1, END1);
		add_elem_env(&g_data.env, tmp);
	}
}

void	execute_cd(char **args, int flag)
{
	char	*old_path;
	char	cwd[4096];

	old_path = ft_strdup(getcwd(cwd, 4097)); // буфер со старой директорией
	if (!old_path)
		end_program("error malloc\n", 1, END1);
	if (flag && (!args[1] || !ft_strcmp(args[1], "~")))
		chdir(getenv("HOME")); // пробуем поменять на домашнюю директорию
	// оработка если есть args[1]
	// вариант ~/
	// относительная или абсолютная директория
	if (flag)
		cd_update_env(old_path); // обновление окружения после cd
}
