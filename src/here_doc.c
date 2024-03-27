#include "../inc/minishell.h"

char	*heredoc_h3(t_tokens **token, char *doc, char *tmp)
{
	char	*line;

	line = NULL;
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
	return (doc);
}

void	heredoc_child(t_tokens **token, t_shell *shell, int *fd)
{
	char	*doc;
	char	*tmp;

	tmp = NULL;
	signal(SIGINT, signal_heredoc);
	doc = NULL;
	doc = heredoc_h3(token, doc, tmp);
	tmp = heredoc_helper2(doc, shell);
	shell->heredoc_len = ft_strlen(tmp);
	write(fd[1], &shell->heredoc_len, sizeof(shell->heredoc_len));
	write(fd[1], tmp, shell->heredoc_len);
	free(tmp);
	close(fd[0]);
	close(fd[1]);
	exit(0);
}

char	*heredoc_parent(int *fd)
{
	int		len;
	ssize_t	bytes;
	char	*buffer;

	len = 0;
	bytes = 0;
	close(fd[1]);
	read(fd[0], &len, sizeof(len));
	buffer = malloc(len + 1);
	bytes = read(fd[0], buffer, len + 1);
	buffer[bytes] = '\0';
	close(fd[0]);
	return (buffer);
}

char	*heredoc(t_tokens **token, t_shell *shell)
{
	pid_t	pid;
	int		fd[2];
	char	*buffer;

	buffer = NULL;
	if (pipe(fd) == -1)
	{
		printf("here_doc pipe error\n");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		heredoc_child(token, shell, fd);
	else
		buffer = heredoc_parent(fd);
	waitpid(pid, &shell->heredocctrlc, 0);
	return (buffer);
}
