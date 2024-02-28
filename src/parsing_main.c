#include "../inc/minishell.h"

void	init_parse(t_parse *p)
{
	p->index = 0;
	p->in_quote = 0;
}

void	parse(t_tokens **tokens, char *line)
{
	t_string	*token;
	t_parse		p;

	init_parse(&p);
	token = NULL;
	while (line[(&p)->index] != 0)
	{
		if (!((&p)->in_quote))
		{
			if (line[(&p)->index] != ' ')
			{
				if (line[(&p)->index] == '|' || line[(&p)->index] == '<'
					|| line[(&p)->index] == '>')
					accopipo(&token, tokens, line, &p);
				else
					quotenizor(&token, line, &p);
			}
			else if (token)
				tokenizor(tokens, &token);
		}
		else if ((&p)->in_quote)
			in_quotenizor(&token, line, &p);
		(&p)->index++;
	}
	end_of_line((&p)->in_quote, token, tokens);
}

// t_tokens	*get_tokens(char *line)
// {
// 	t_tokens	*l_tokens;

// 	l_tokens = NULL;
// 	parse(&l_tokens, line);
// 	return (l_tokens);
// }

// int	main(int argc, char *argv[])
// {
// 	t_tokens	*l_tokens;

// 	if (argc != 2)
// 	{
// 		printf("Need 1 argument!\n");
// 		exit(0);
// 	}
// 	l_tokens = get_tokens(argv[1]);
// 	printf("~~~~~\nString to parse: |%s|\n\nFound tokens:\n", argv[1]);
// 	print_tokens(l_tokens);
// 	printf("~~~~~\n");
// 	free_tokens(l_tokens);
// 	return (0);
// }
