#include "../inc/minishell.h"

void	quotexor(int *in_quote, char c)
{
	if (c == '\'')
	{
		if (*in_quote == 1)
			*in_quote = 0;
		else if (*in_quote == 0)
			*in_quote = 1;
	}
	if (c == '"')
	{
		if (*in_quote == 2)
			*in_quote = 0;
		else if (*in_quote == 0)
			*in_quote = 2;
	}
}

void	interpret_dollar(t_string **str, char *line, int *index, t_shell *shell)
{
	t_string	*var_name;
	char		*var;
	char		*env;
	int			i;

	var_name = NULL;
	*index += 1;
	while (line[*index] != 0 && (ft_isalnum(line[*index])
			|| line[*index] == '_'))
	{
		add_char(&var_name, line[*index]);
		*index += 1;
	}
	var = get_string(var_name);
	free_string(var_name);
	env = get_env(shell->env, var);
	free(var);
	i = 0;
	while (env && env[i])
	{
		add_char(str, env[i]);
		i++;
	}
	free(env);
}

char	*parse_env_var(char *line, t_shell *shell)
{
	t_string	*str;
	int			index;
	char		*ret;
	int			in_quote;

	index = 0;
	str = NULL;
	in_quote = 0;
	while (line[index])
	{
		if (line[index] == '$' && in_quote != 1)
			interpret_dollar(&str, line, &index, shell);
		else
		{
			quotexor(&in_quote, line[index]);
			add_char(&str, line[index]);
			index++;
		}
	}
	ret = get_string(str);
	free_string(str);
	return (ret);
}
