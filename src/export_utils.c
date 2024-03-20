#include "../inc/minishell.h"

char	*add_quote_export(char *env)
{
	char		*line;
	char		*cut;
	char		*quote;
	char		*tmp;
	int			i;

	i = 0;
	cut = NULL;
	quote = ft_strdup("\"");
	while (env[i])
	{
		if (env[i] == '=')
			cut = ft_substr(env, i + 1, ft_strlen(env));
		i++;
	}
	tmp = ft_strjoin(quote, cut);
	line = ft_strjoin(tmp, quote);
	free(tmp);
	free(quote);
	free(cut);
	return (line);
}

char	*get_base_export(char *env, char *tmp)
{
	int		i;
	int		len;
	char	*cut;

	i = 0;
	len = ft_strlen(env) - ft_strlen(tmp) + 3;
	cut = malloc(len * sizeof(char));
	while (env[i])
	{
		cut[i] = env[i];
		if (env[i] == '=')
			break ;
		i++;
	}
	i++;
	cut[i] = '\0';
	return (cut);
}

char	*fuse_export(char *env)
{
	char	*declare;
	char	*tmp;
	char	*bit;
	char	*line;

	bit = add_quote_export(env);
	declare = ft_strdup("declare -x ");
	tmp = ft_strjoin(declare, get_base_export(env, bit));
	line = ft_strjoin(tmp, bit);
	free(bit);
	free(declare);
	free(tmp);
	return (line);
}

char **ulti_fuse_export(char **env)
{
	char	**export;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	export = malloc((len + 1) * sizeof(char *));
	while(env[i])
	{
		export[i] = fuse_export(env[i]);
		i++;
	}
	export[i] = NULL;
	return (export);
}
