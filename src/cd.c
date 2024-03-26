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

int	ft_cd(char **a_arg, t_shell *shell)
{
	int		index;
	char	*home;

	index = 0;
	if (!a_arg[1])
	{
		index = find_var_index("HOME", shell->env);
		if (index > -1)
		{	
			home = home_path(shell->env, index);
			if (is_directory(home))
				chdir(home);
			else
				printf("%s: No such file or directory\n", home);
			free(home);
		}
		else
			printf("cd: HOME not set\n");
	}
	else if (chdir(a_arg[1]) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
