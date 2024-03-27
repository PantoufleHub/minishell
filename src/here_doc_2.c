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

void	signal_heredoc(int signum)
{
	signum = 0;
	exit(80085);
}
