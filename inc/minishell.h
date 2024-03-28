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
# include <sys/stat.h>
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

char					*parse_env_var(char *line, t_shell *shell);

void					print_tokens(t_tokens *l_tokens);

void					add_token(t_tokens **l_tokens, char *token,
							int is_meta);

int						string_len(t_string *string);

char					*get_string(t_string *string);

void					add_char(t_string **string, char c);

void					free_string(t_string *string);

void					free_tokens(t_tokens *tokens);

int						end_of_line(int in_quote, t_string *token,
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

int						parse(t_tokens **tokens, char *line);

int						last_chevron(t_tokens *token);

int						chevron_meta(t_tokens *token);

int						pipo_syntax(t_tokens *token);

int						syntax_check(t_tokens *token);

int						dub_dub_chev(t_tokens *token);

int						dub_pipo(t_tokens *token);

char					*get_cmd(char **paths, char *cmd);

int						args_size(t_list_arg *args);

void					init_cmd_st(t_cmd *new_cmd);

void					add_cmd_and_type_utils(char *cmd,
							t_tokens *token, t_cmd *st_cmd, char **path);

int						add_cmd_and_type(t_tokens *token,
							t_cmd *st_cmd, char **path);

void					add_arg(t_cmd *cmd_st, char *arg);

int						store_chevron(t_cmd **cmd_st, t_tokens **token,
							t_shell *shell);

int						chev_utils(t_cmd **cmd_st, t_tokens **token, int a);

int						chev_utils_bis(t_cmd **cmd_st, t_tokens **token, int a,
							t_shell *shell);

void					fill_cmd_st(t_cmd *new_cmd, t_tokens *current_token,
							char **path, t_shell *shell);

t_cmd					*bag_to_cmd(t_tokens *bag, char **path, t_shell *shell);

t_list					*get_bags_list(t_tokens *tokens);

t_list_cmd				*get_list_cmds_from_bags(t_list *bags, char **path,
							t_shell *shell);

char					*heredoc(t_tokens **token, t_shell *shell);

t_tokens				*get_tokens(char *line);

void					exec_commands(t_shell *shell, t_list_cmd *list_cmd);

int						echo_wo_n(char **av);

int						echo_w_n(char **av);

int						n_count_echo(char **av);

int						ft_echo(char **av);

int						ft_cd(char **a_arg, t_shell *shell);

int						ft_pwd(void);

int						ft_exit(int status);

int						exec_builtin(t_cmd *cmd, t_shell *shell);

int						ft_env(t_shell *shell);

void					init_shell(t_shell *shell, char **env);

int						ft_export(char **a_arg, t_shell *shell);

void					destroy_shell(t_shell *shell);

char					*ft_strncpy(char *dest, const char *src, size_t n);

char					*copy_until_char_or_all(char *src, char c);

void					print_export(t_shell *shell);

int						export_syntax(char *arg);

void					free_arr_str(char **str);

int						count_env_vars(char **env);

int						find_var_index(char *key, char **env);

void					var_utils_helper(char *a_arg, char **new, int *found,
							int i);

void					var_utils(char **env, char *a_arg, char **new,
							int env_len);

char					**add_var_env(char **export, char *a_arg);

int						count_cmds(t_list_cmd *cmds);

char					*get_env(char **envp, char *var);

int						ft_unset(t_shell *shell, char **a_arg);

void					exec_command(t_cmd	*cmd, char **env);

void					exec_commands(t_shell *shell, t_list_cmd *list_cmd);

void					close_paips(int **paips);

int						**init_paips(int nb_paips);

void					set_paip(t_cmd *cmd, int *paips[], int cmd_nb);

void					set_in_out(t_cmd *cmd);

void					clean_list_bag(t_list *list_bag);

void					clean_list_arg(t_list_arg *args);

void					free_str(char **str);

void					clean_cmd_str(t_cmd *cmd);

void					clean_list_cmd(t_list_cmd *list_cmd);

void					clean_tokens(t_tokens *tokens);

void					clean_swag(t_list_cmd *list_cmd, t_list *list_bag,
							char **paths, t_tokens *tokens);

void					signal_handler_child(int signum);

void					signal_heredoc(int signum);

char					*heredoc_helper2(char *doc, t_shell *shell);

int						heredoc_helper(t_tokens **token, char *line);

int						chev_utils2(t_tokens **token);

void					chev_utils_bis2(t_cmd **cmd_st,
							t_tokens **token, int a, t_shell *shell);

void					sigterm(void);

void					interpret_line_helper(t_tokens *tokens, t_shell *shell);

void					give_money(t_string *var_name, char *env,
							t_shell *shell, t_string **str);

void					quotexor(int *in_quote, char c);

char					*unquotor(char *token);

void					unquotokenator(t_tokens *tokens);

#endif