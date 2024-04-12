/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:59:18 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 16:50:56 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./libft/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h> 
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <limits.h>

// ANSI COLORS
# define ANSI_BOLD "\x1B[1m"
# define ANSI_MAG "\x1B[35m"
# define ANSI_RESET "\x1B[0m"
# define ANSI_BLUE "\x1B[34m"
# define ANSI_YEL "\x1B[33m"
# define ANSI_RED "\x1B[31m"
# define ANSI_WBG "\x1B[47m"

extern int	g_exit_code;

typedef struct s_cmd
{
	int				id;
	char			**cmd_list;
	int				output;
	int				input;
	int				pb;
	bool			pipe;
	pid_t			pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef enum e_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT_APPEND,
	TOKEN_HEREDOC,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN
}	t_type;

typedef struct s_token
{
	char			*content;
	t_type			flag_type;
	int				dollar;
	int				i;
	int				end;
	t_list			*list;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_hash_item
{
	char				*key;
	char				*value;
	struct s_hash_item	*next;
}	t_hash_item;

typedef struct s_hash_table
{
	int			size;
	t_hash_item	**items;
}	t_hash_table;

typedef struct s_minishell
{
	int				i;
	int				end;
	char			*input;
	char			**env;
	int				len;
	char			**cmd;
	char			**dir_list;
	t_hash_table	*hash;
	t_token			*token;
	t_cmd			*command;
}	t_minishell;

// MAIN
void				init_shell(t_minishell *minishell, char **env);
void				free_minishell(t_minishell *minishell);

/// SHELL ///
// core
void				start_up_shell(void);
void				reset_shell(t_minishell *minishell);

// error
void				print_err(char *msg, char *suffix, int error);
void				simple_err(char *msg, char *suffix, int error);

// HASH
unsigned long int	hash_function(char *key, unsigned int size);
t_hash_table		*new_hash(int array_len);
t_hash_item			*hash_new_item(char *key, char *value);
t_hash_item			*hash_new_item(char *key, char *value);
char				*retrieve_value(t_hash_table *hash, char *key);
void				hash_insert_duo(t_hash_table *hash, char *key, char *value);
char				*retrieve_value(t_hash_table *hash, char *key);
void				hash_insert_duo(t_hash_table *hash, char *key, char *value);
void				free_hash(t_hash_table *hash);
void				free_hash_item(t_hash_item *item);
void				hash_delete_duo(t_hash_table *hash, char *key);
void				print_hash(t_hash_table *hash);

// ENV
t_hash_table		*env_to_hash(char **env);
int					find_delim(char *str, char c);

// SIGNAL
void				config_signal(void);
void				config_child_signal(void);

//TOKENIZER
void				split_token(char *input, t_minishell *minishell);
int					dismiss_input(t_minishell *minishell, char *input);
void				tokenizer(t_minishell *minishell);

//TRIMMER
void				trim_quotes(char *input, t_minishell *minishell, int start);
void				special_plus_one(char *input, t_minishell *minishell);
void				special_plus_two(char *input, t_minishell *minishell);
void				special_trim(char *input, t_minishell *minishell);
void				regular_trim(char *input, t_minishell *m);
//TOKEN LIST UTILS
int					token_type(char *input);
void				clear_token(t_token **list);
t_token				*token_last(t_token *lst);
void				add_back_token(t_token **token, t_token *new);
t_token				*token_new(char *content, int flag_type);

//LOGICAL EXPRESSION TEsts
int					is_white_space(char c);
int					is_quote(char c);
int					is_splitter(char *c, int i);
int					is_equal(char *str);
void				quote_loop(t_minishell *m, char *input);

//lexical scanner
int					is_valid_quote(t_token *token);
int					is_valid_redir(t_token *token);
int					is_valid_scenario(t_token *token);
int					is_valid_pipe(t_token *token, int index);
int					check_grammar(t_minishell *minishell);

// EXPANSION
void				expand_token(t_minishell *minishell);
void				check_paramexp(t_token *token, t_minishell *minishell);
void				remove_dollar_before_single(t_token *token, int i);
void				trim_out_dollar(t_token *token, int i);

// dollar expansion
void				exp_dollar(t_token *token, int idx, t_minishell *minishell);
void				expand_value(t_token *token, t_minishell *minishell);
void				extract_rest(t_token *token);
void				retrieve_expansion(t_minishell *minishell, t_token *token);
char				*join_expanded(t_list *expanded_list);
void				free_list(t_list *list);
void				list_clear(t_list **list, void (*del)(void *));
int					find_end(char *str, int i);
int					is_regular_delim(char c);
int					get_key_end(char *str, int idx);
int					is_dollar_delimiter(char c);

// quotes
void				define_quote_type(t_token *token);
void				remove_quotes(t_token *token);
void				keep_one_remove_other(t_token *token, char c);

// COMMAND
void				prep_command(t_cmd **comm, t_minishell *minishell);

// command utils
t_cmd				*init_cmd(int size);
void				cmd_delone(t_cmd *cmd, void (*del)(void *));
void				cmd_clear(t_cmd **cmd, void (*del)(void *));
int					cmd_lst_size(t_token *token);
void				cmd_addback(t_cmd **list, t_cmd *new);
t_cmd				*cmd_new(int len);
int					list_len(t_token **token);

// parse redir
t_token				*parse_redir_out(t_cmd *cmd, t_token *token);
t_token				*parse_redir_in(t_cmd *cmd, t_token *token, t_minishell *m);
t_token				*parse_redir(t_cmd *cmd, t_token *token, t_minishell *m);
t_token				*parse_heredoc(t_cmd *cmd, t_token *token, t_minishell *m);

// parse command
t_token				*parse_word(t_token *token, t_cmd *cmd);

// parse pipe
t_cmd				*parse_pipe(t_cmd *cmd, t_minishell *minishell);

// redir
int					redir_in(t_cmd *cmd, char *file_name);
void				redir_out(t_cmd *cmd, char *file_name);
void				redir_out_append(t_cmd *cmd, char *file_name);
int					is_ambiguous_redir(char *file_name, t_cmd *cmd);
int					is_valid_filename(t_cmd *cmd, char *file_name);
void				init_io(t_cmd *cmd);
void				make_here_doc(char *delim, t_minishell *m, t_cmd *cmd);

// EXECUTION
void				prep_execution(t_minishell *minishell);
void				exec_loop(t_minishell *minishell);
int					exec_builtin(t_cmd *cmd, char *name, t_minishell *m);
int					is_builtin(char *cmd);
void				exec_pipe(t_cmd *cmd, t_minishell *minishell);
void				exec_cmd(t_cmd *cmd, t_minishell *minishell);
int					execute(t_minishell *minishell, t_cmd *cmd);
void				post_processing(t_minishell *minishell);

// FD
t_cmd				*reset_cmd_fd(t_cmd *cmd);
void				close_fd(t_minishell *minishell);
void				close_cmd_fd(t_minishell *minishell);

//path
char				**find_path_list(t_minishell *minishell, t_cmd *cmd);
char				*find_executable(char **dir_list, char *command);
void				not_found_error(char *command);
int					is_dir(char *cmd);
int					check_access(char *exec_test);
char				*dir_err(char **dir, char *comm, char *test, char *cmd);
char				*valid_access(char **dir_list, char *cmd, char *exec_test);
void				not_found_error(char *command);

// BUILTINS
void				exec_pwd(t_cmd *cmd);
void				exec_echo(char **cmd, t_cmd *comm);
void				exec_env(char **cmd, t_minishell *minishell, t_cmd *c);
void				exec_cd(char **cmd, t_minishell *minishell);
void				ch_dir_err(char *path, char *old_wd, char *old_buff);
void				get_cwd_err(char *wd, char *buff);
void				update_pwd(t_minishell *minishell);
void				exec_export(char **cmd, t_minishell *minishell, t_cmd *c);
void				exec_unset(char **cmd, t_minishell *minishell);
void				exec_exit(char **cmd, t_minishell *minishell);

// FREE AND CLEAR
void				free_array(char **cmd);
void				free_str(char *str);
void				free_exec_cmd(t_minishell *minishell);
int					free_execute_pb(t_minishell *minishell);

// UTILS
int					array_len(char **array);
char				**get_env_from_hash(t_minishell *minishell);
char				*fill_key_equals_value(t_hash_item *item);
long long int		ft_atol(char *str);

// CURRENT DIRECTORY getcwd
# define BUFFER 50

# define MUTE 1000
#endif
