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

typedef struct s_list_arg
{
	char				*arg;
	struct s_list_arg	*next;
}	t_list_arg;

//append mode is to differenciate between overwriting a file >
// and appending to a file >> in output redirections.
//I propose: 0 false > overwrite (0_TRUNC)     |    1 true >> append (0_APPEND)
//
typedef struct s_cmd
{
	t_cmd_type	cmd_type;
	char		*cmd;
	t_list_arg	*args;
	char		**a_arg;
	char		*infile;
	int			doc;
	char		*outfile;
	char		*heredoc;
	int			append;
	int			error;
	int			fd_in;
	int			fd_out;
}	t_cmd;

typedef struct s_list_cmd
{
	t_cmd				*cmd;
	struct s_list_cmd	*next;
}	t_list_cmd;

#endif