#include "../inc/minishell.h"

int	heredoc_helper(t_tokens **token, char *line)
{
	if (!line)
		return (1);
	if (!(ft_strncmp((*token)->token, line, ft_strlen((*token)->token)))
		&& !(ft_strncmp((*token)->token, line, ft_strlen(line))))
	{
		free (line);
		return (1);
	}
	return (0);
}

char	*heredoc(t_tokens **token, t_shell *shell)
{
	char	*line;
	char	*doc;
	char	*tmp;

	doc = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (heredoc_helper(token, line))
			break ;
		tmp = doc;
		doc = ft_strjoin(tmp, "\n");
		free(tmp);
		tmp = doc;
		doc = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	tmp = doc;
	doc = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = parse_env_var(doc, shell);
	free(doc);
	return (tmp);
}
