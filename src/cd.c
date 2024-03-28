#include "../inc/minishell.h"

char	*key_path(char **env, int index, int key_len)
{
	int		i;
	int		len;
	char	*home_path;

	i = 0;
	len = ft_strlen(env[index]) - key_len;
	home_path = ft_substr(env[index], key_len, len);
	return (home_path);
}

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	cd_helper(t_shell *shell, int index)
{
	char	*home;

	home = key_path(shell->env, index, 5);
	if (is_directory(home))
	{
		chdir(home);
		free(home);
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("%s: No such file or directory\n", home);
		free(home);
		return (EXIT_FAILURE);
	}
}

int	cd_minus(t_shell *shell)
{
	int		index;
	char	*oldpwd;

	oldpwd = NULL;
	index = find_var_index("OLDPWD", shell->env);
	if (index >= 0)
		oldpwd = key_path(shell->env, index, 7);
	if (is_directory(oldpwd))
	{
		chdir(oldpwd);
		free(oldpwd);
		ft_pwd();
		return (EXIT_SUCCESS);
	}
	else
	{
		printf("cd: OLDPWD not set\n");
		free(oldpwd);
		return (EXIT_FAILURE);
	}
}

int	ft_cd(char **a_arg, t_shell *shell)
{
	int		index;

	index = 0;
	if (!a_arg[1])
	{
		index = find_var_index("HOME", shell->env);
		if (index > -1)
			return (cd_helper(shell, index));
		else
		{
			printf("cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
	}
	else if (ft_strncmp(a_arg[1], "-", 1) == 0)
		return (cd_minus(shell));
	else if (chdir(a_arg[1]) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
