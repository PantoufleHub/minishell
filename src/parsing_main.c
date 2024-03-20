#include "../inc/minishell.h"

void	init_parse(t_parse *p)
{
	p->index = 0;
	p->in_quote = 0;
}

int	parse(t_tokens **tokens, char *line)
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
	return (end_of_line((&p)->in_quote, token, tokens));
}
