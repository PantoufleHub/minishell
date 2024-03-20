#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG printf("File: %s, Line: %d\n", __FILE__, __LINE__);

# include <stdio.h>
# include <stdlib.h>
# include <histedit.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
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

void					interpret_line(char *line, t_shell *shell);

void					set_signals(void);

void					set_signals_child(void);

void					signal_handler(int signum);

char					*strings_join(char **arr);

size_t					word_count(const char *s, const char c);

char					**ft_split_p(const char *s, const char c);

char					*parse_env_var(char *line, t_shell *shell);

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

t_tokens				*get_tokens(char *line);

void					exec_commands(t_shell *shell, t_list_cmd *list_cmd);

int						echo_wo_n(char **av);

int						echo_w_n(char **av);

int						n_count_echo(char **av);

int						ft_echo(char **av);

int						ft_cd(char **a_arg);

int						ft_pwd(void);

void					ft_exit(int status);

void					exec_builtin(t_cmd *cmd, t_shell *shell);

int						ft_env(t_shell *shell);

void					init_shell(t_shell *shell, char **env);

void					ft_export(char **a_arg, t_shell *shell);

void					destroy_shell(t_shell *shell);

char					*ft_strncpy(char *dest, const char *src, size_t n);

char					*copy_until_char_or_all(char *src, char c);

void					print_export(t_shell *shell);

int						export_syntax(char *arg);

void					free_arr_str(char **str);

int						count_env_vars(char **env);

int						find_var_index(char *key, char **env);

void					var_utils_helper(char *a_arg, char **new, int *found, int i);

void					var_utils(char **env, char *a_arg, char **new, int env_len);

char					**add_var_env(char **export, char *a_arg);

void					ft_export(char **a_arg, t_shell *shell);

int						count_cmds(t_list_cmd *cmds);

char					*get_env(char **envp, char *var);

#endif