#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_dim
{
	size_t	x;
	size_t	y;
}	t_dim;

typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_string
{
	char			c;
	struct s_string	*next;
}	t_string;

typedef struct s_parse
{
	int			index;
	int			in_quote;
}	t_parse;

//CMD_EXTERNAL for commands exectued via execve
//CMD_BUILTIN for built-in shell commands that we have to do
typedef enum e_cmd_type
{
	CMD_EXTERNAL,
	CMD_BUILTIN
}	t_cmd_type;

typedef struct s_cmd
{
	t_cmd_type	cmd_type;
	char		*cmd;
	char		**args;
	char		*infile;
	char		*outfile;
	int			append;
	int			fd_in;
	int			fd_out;
}	t_cmd;

#endif