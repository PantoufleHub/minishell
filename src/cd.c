#include "../inc/minishell.h"

char	*home_path(char **env, int index)
{
	int		i;
	int		len;
	char	*home_path;

	i = 0;
	len = ft_strlen(env[index]) - 5;
	home_path = ft_substr(env[index], 5, len);
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

	home = home_path(shell->env, index);
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
	else if (chdir(a_arg[1]) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
