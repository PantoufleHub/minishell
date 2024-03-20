#include "../inc/minishell.h"

int	ft_env(t_shell *shell)
{
	int		i;
	char	*equal;

	i = 0;
	equal = NULL;
	if (!shell->env)
		return (0);
	while (shell->env[i])
	{
		equal = ft_strchr(shell->env[i], '=');
		if (equal)
			printf("%s\n", shell->env[i]);
		i++;
	}
	return (0);
}

// int main(int ac, char **av, char **env)
// {
//     ac = 0;
//     av = NULL;
//     ft_env(env);
//     return (0);
// }