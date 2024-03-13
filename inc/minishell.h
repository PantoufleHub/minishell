#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <histedit.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"
# include "structure.h"
# include "constants.h"

void					broken_pipe(void);

void					restore_terminal(struct termios *save);

void					set_terminal(struct termios *save);

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

char					*get_cmd(char **paths, char *cmd);

int						args_size(t_list_arg *args);

void					init_cmd_st(t_cmd *new_cmd);

void					add_cmd_and_type_utils(char **cmd,
	t_tokens *token, t_cmd *st_cmd, char **path);

int						add_cmd_and_type(t_tokens *token,
	t_cmd *st_cmd, char **path);

void					add_arg(t_cmd *cmd_st, char *arg);

int						store_chevron(t_cmd **cmd_st, t_tokens **token);

int						chev_utils(t_cmd **cmd_st, t_tokens **token, int a);

int						chev_utils_bis(t_cmd **cmd_st, t_tokens **token, int a);

void					fill_cmd_st(t_cmd *new_cmd,
	t_tokens *current_token, char **path);

t_cmd					*bag_to_cmd(t_tokens *bag, char **path);

t_list					*get_bags_list(t_tokens *tokens);

t_list_cmd				*get_list_cmds_from_bags(t_list *bags, char **path);

t_list_cmd				*get_cmds_from_tokens(t_tokens *tokens, char **path);

char					*heredoc(t_tokens **token);

int						echo_wo_n(t_list_arg *args);

int						echo_w_n(t_list_arg *args);

int						ft_echo(t_list_arg *args);

int						n_count_echo(t_list_arg *args);

t_tokens				*get_tokens(char *line);

void					exec_commands(t_list_cmd *list_cmd, char **env);

#endif