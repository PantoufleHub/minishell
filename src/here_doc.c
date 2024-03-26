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

char	*heredoc_helper2(char *doc, t_shell *shell)
{
	char	*tmp;

	if (!doc)
		doc = ft_strdup("");
	if (doc[0] != '\0')
	{
		tmp = doc;
		doc = ft_strjoin(tmp, "\n");
		free(tmp);
	}
	tmp = parse_env_var(doc, shell);
	free(doc);
	return (tmp);
}

char	*heredoc(t_tokens **token, t_shell *shell)
{
	char	*line;
	char	*doc;
	char	*tmp;

	doc = NULL;
	while (1)
	{
		line = readline("> ");
		if (heredoc_helper(token, line))
			break ;
		if (!doc)
			doc = ft_strdup(line);
		else
		{
			tmp = doc;
			doc = ft_strjoin(tmp, "\n");
			free(tmp);
			tmp = doc;
			doc = ft_strjoin(tmp, line);
			free(tmp);
		}
		free(line);
	}
	tmp = heredoc_helper2(doc, shell);
	return (tmp);
}
