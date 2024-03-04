#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <histedit.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "structure.h"
# include "constants.h"

void					broken_pipe(void);

void					display_prompt(void);

void					exit_with_error(char *message);

void					entry_display(void);

void					error_message(char *message);

char					**get_paths(char *envp[]);

char					*get_prompt(void);

void					interpret_line(char *line, char *envp[]);

void					set_signals(void);

void					set_signals_child(void);

void					signal_handler(int signum);

char					*strings_join(char **arr);

size_t					word_count(const char *s, const char c);

char					**ft_split_p(const char *s, const char c);

char					*parse_env_var(char *line);

char					*trim_sp(char **split);

void					print_tokens(t_tokens *l_tokens);

void					add_token(t_tokens **l_tokens, char *token);

int						string_len(t_string *string);

char					*get_string(t_string *string);

void					add_char(t_string **string, char c);

void					free_string(t_string *string);

void					free_tokens(t_tokens *tokens);

void					end_of_line(int in_quote, t_string *token,
							t_tokens **tokens);

void					acco_tokenizor(t_string **token, t_tokens **tokens,
							char *line, t_parse *p);

void					pipo_tokenizor(t_string **token, t_tokens **tokens,
							char *line, t_parse *p);

void					quotenizor(t_string **token, char *line, t_parse *p);

void					tokenizor(t_tokens **tokens, t_string **token);

void					in_quotenizor(t_string **token, char *line, t_parse *p);

void					accopipo(t_string **token, t_tokens **tokens,
							char *line, t_parse *p);

void					init_parse(t_parse *p);

void					parse(t_tokens **tokens, char *line);

int						last_chevron(t_tokens *token);

int						chevron_meta(t_tokens *token);

int						pipo_syntax(t_tokens *token);

int						syntax_check(t_tokens *token);

int						dub_dub_chev(t_tokens *token);

int						token_count(t_tokens *token);

void					add_cmd_node(t_list_cmd **cmds, t_cmd *st_cmd);

void					add_cmd_and_type(t_tokens *token,
	t_cmd *st_cmd, char **path);

char					*get_cmd(char **paths, char *cmd);

#endif