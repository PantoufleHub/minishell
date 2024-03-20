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
		i++;
	}
	free(key);
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
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
		free(str);
}

int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env[count])
		count ++;
	return (count);
}

// char	*add_quote_export(char *env)
// {
// 	char		*line;
// 	char		*cut;
// 	char		*quote;
// 	char		*tmp;
// 	int			i;

// 	i = 0;
// 	cut = NULL;
// 	quote = ft_strdup("\"");
// 	while (env[i])
// 	{
// 		if (env[i] == '=')
// 			cut = ft_substr(env, i + 1, ft_strlen(env));
// 		i++;
// 	}
// 	tmp = ft_strjoin(quote, cut);
// 	line = ft_strjoin(tmp, quote);
// 	free(tmp);
// 	free(quote);
// 	free(cut);
// 	return (line);
// }

// char	*get_base_export(char *env, char *tmp)
// {
// 	int		i;
// 	int		len;
// 	char	*cut;

// 	i = 0;
// 	len = ft_strlen(env) - ft_strlen(tmp) + 3;
// 	cut = malloc(len * sizeof(char));
// 	while (env[i])
// 	{
// 		cut[i] = env[i];
// 		if (env[i] == '=')
// 			break ;
// 		i++;
// 	}
// 	i++;
// 	cut[i] = '\0';
// 	return (cut);
// }

// char	*fuse_export(char *env)
// {
// 	char	*declare;
// 	char	*tmp;
// 	char	*bit;
// 	char	*line;

// 	bit = add_quote_export(env);
// 	declare = ft_strdup("declare -x ");
// 	tmp = ft_strjoin(declare, get_base_export(env, bit));
// 	line = ft_strjoin(tmp, bit);
// 	free(bit);
// 	free(declare);
// 	free(tmp);
// 	return (line);
// }

// char **ulti_fuse_export(char **env)
// {
// 	char	**export;
// 	int		i;
// 	int		len;

// 	i = 0;
// 	len = 0;
// 	while (env[len])
// 		len++;
// 	export = malloc((len + 1) * sizeof(char *));
// 	while(env[i])
// 	{
// 		export[i] = fuse_export(env[i]);
// 		i++;
// 	}
// 	export[i] = NULL;
// 	return (export);
// }
