# include "../inc/minishell.h"

void	init_shell_utils(t_shell *shell, char **env)
{
	int		i;
	int		len;

	i = 0;
	while (env[i])
		i++;
	shell->vars = malloc((i + 1) * sizeof(t_var));
	shell->env = malloc((i + 1) * sizeof(char *));
	i = 0;
	len = 0;
	while (env[i])
	{
		len = 0;
		while (env[i][len] != '=')
			len++;
		shell->vars[i] = malloc(sizeof(t_var));
		shell->vars[i]->key = malloc(len + 1);
		shell->vars[i]->key = ft_strncpy(shell->vars[i]->key, env[i], len);
		shell->vars[i]->key[len] = '\0';
		shell->vars[i]->value = ft_substr(env[i], len + 1, ft_strlen(env[i]) - len + 1);
		shell->env[i] = ft_strdup(env[i]);
		i++;
	}
	shell->vars[i] = NULL;
	shell->env[i] = NULL;
}

void	init_shell(t_shell *shell, char **env)
{
	set_signals();
	set_terminal(&(shell->term_save));
	entry_display();
	shell->dollar_question_mark = 0;
	init_shell_utils(shell, env);
}

void	destroy_shell(t_shell *shell)
{
	restore_terminal(&(shell->term_save));
}
