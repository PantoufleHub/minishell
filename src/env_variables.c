#include "../inc/minishell.h"

void	quotexor(int *in_quote, char c)
{
	if (c == '\'')
	{
		if (*in_quote == 1)
			*in_quote = 0;
		if (*in_quote == 0)
			*in_quote = 1;
	}
	if (c == '"')
	{
		if (*in_quote == 2)
			*in_quote = 0;
		if (*in_quote == 0)
			*in_quote = 2;
	}
}

void	interpret_dollar(t_string **str, char *line, int *index)
{
	t_string	*var_name;
	char		*var;
	char		*env;
	int			i;

	var_name = NULL;
	*index += 1;
	while (line[*index] != 0 && ft_isalnum(line[*index]))
	{
		add_char(&var_name, line[*index]);
		*index += 1;
	}
	var = get_string(var_name);
	free_string(var_name);
	env = getenv(var);
	free(var);
	i = 0;
	while (env && env[i])
	{
		add_char(str, env[i]);
		i++;
	}
}

char	*parse_env_var(char *line)
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
			interpret_dollar(&str, line, &index);
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

// int	main(int argc, char *argv[], char *envp[])
// {
// 	if (argc != 2)
// 		exit(0);
// 	// printf("ENV: %s\n", getenv(NULL));
// 	// printf(CYN"Var: %s\n"RED"Expected:  %s\n"YEL"Got value: %s\n"NRM, argv[1], getenv(argv[1]+1), get_env_var(argv[1], envp));
// 	char *s= parse_env_var(argv[1]);
// 	printf(YEL"%s\n"NRM, s);
// 	free(s);
// 	return (0);
// }
