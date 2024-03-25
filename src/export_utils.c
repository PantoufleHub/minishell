#include "../inc/minishell.h"

char	*copy_until_char_or_all(char *src, char c)
{
	char	*pos;
	char	*dest;
	size_t	i;

	i = 0;
	pos = ft_strchr(src, c);
	dest = NULL;
	if (!pos)
		i = ft_strlen(src);
	else
		i = pos - src;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	ft_strncpy(dest, src, i);
	dest[i] = '\0';
	return (dest);
}

void	print_export(t_shell *shell)
{
	int		i;
	char	*equal;
	char	*key;
	char	*quote;

	i = 0;
	equal = NULL;
	key = NULL;
	quote = NULL;
	while (shell->env[i])
	{
		key = copy_until_char_or_all(shell->env[i], '=');
		equal = ft_strchr(shell->env[i], '=');
		quote = ft_strchr(shell->env[i], '\"');
		if (!equal)
			printf("declare -x %s\n", key);
		else if (!quote)
			printf("declare -x %s=\"%s\"\n", key, equal + 1);
		else
			printf("declare -x %s=%s\n", key, equal + 1);
		free(key);
		i++;
	}
}

int	export_syntax(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	if (!((arg[0] >= 'A' && arg[0] <= 'Z')
			|| (arg[0] >= 'a' && arg[0] <= 'z') || arg[0] == '_'))
	{
		printf("export : %s: not a valid identifier\n", arg);
		return (0);
	}
	while (arg[i])
	{
		if (!((arg[i] >= 'A' && arg[i] <= 'Z')
				|| (arg[i] >= 'a' && arg[i] <= 'z')
				|| (arg[i] >= '0' && arg[i] <= '9')
				|| arg[i] == '_' || arg[i] == '='))
		{
			printf("export : %c: not a valid identifier\n", arg[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_arr_str(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str && str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count ++;
	return (count);
}
