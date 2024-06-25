/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:43:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/25 19:00:47 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# define PROMPT "mini-shell$ "
# define ERR_PROMPT "mini-shell: "
# define WHITESPACES " \t\v\f\r"

# define SYNTAX_ERR "syntax error near unexpected token"
# define STDIN_FILENO 0
# define STDOUT_FILENO 1

enum
{
	READ_END,
	WRITE_END
};

enum
{
	NODE_REDIR,
	NODE_WORD,
	NODE_CMD,
	NODE_PIPE,
	NODE_OR,
	NODE_AND
};

enum
{
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND
};

typedef struct s_env
{
	char			*key;
	char			*value;
	int				index;
	bool			is_equal;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*value;
	int				type;
	int				index;
	bool			is_parsed;
	bool			is_space;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_heredoc
{
	char			*file;
	char			*stop_key;
	int				fd;
	bool			exists;
}	t_heredoc;

typedef struct s_redir_in
{
	char			*file;
	int				fd;
	bool			exists;
}	t_redir_in;

typedef struct s_redir_out
{
	char			*file;
	int				fd;
	bool			exists;
}	t_redir_out;

typedef struct s_redir_append
{
	char			*file;
	int				fd;
	bool			exists;
}	t_redir_append;

typedef struct s_ast
{
	int				end_flag;
	int				type;
	int				pipe[2];
	int				*in_fd;
	int				*out_fd;
	int				*prev_pipe;
	bool			pipe_exists;
	bool			prev_exists;
	t_redir_in		*redir_in;
	t_redir_out		*redir_out;
	t_redir_append	*redir_append;
	t_heredoc		*heredoc;
	char			**cmd;
	struct s_ast	*head;
	struct s_ast	*left;
	struct s_ast	*right;
	t_token			*token;
}	t_ast;

typedef struct s_child
{
	t_ast			*ast;
	pid_t			pid;
}	t_child;

typedef struct s_data
{
	int				curr_pid;
	int				cmd_count;
	t_child			*pids;
	bool			error;
	char			*line;
	char			**path;
	char			**env;
	char			**env_arr;
	int				exit_status;
	t_env			*env_list;
	t_token			*tokens;
	t_ast			*ast;
}	t_data;

//  ************ Parsing Function ************  //
bool	lexer(t_data *data);
t_ast	*parser(t_data *data);

// ***** Parsing Utils Functions ***** //
t_ast	*parse_cmd(t_token *token, t_ast *new_node);
int		count_cmds(t_ast *ast, t_data *data);
void	check_left_for_redir(t_token *token, t_ast *right_node);
void	check_right_for_redir(t_token *token, t_ast *right_node);

//	*-> Env Functions
t_env	*env_get(t_data *data, char *key);
t_env	*env_last(t_data *data);
char	*env_expansion(t_data *data, char *str);
void	env_new(t_data *data, char *key, char *value, bool is_equal );
void	env_set(t_data *data, char *key, char *value, bool is_equal );
void	env_concat(t_data *data, char *key, char *value);
void	env_new(t_data *data, char *key, char *value, bool is_equal );
void	env_set(t_data *data, char *key, char *value, bool is_equal );
void	env_concat(t_data *data, char *key, char *value);
void	env_add(t_data *data, t_env *new);
void	env_lstclear(t_data *data);
void	env_tolst(t_data *data);
void	env_toarr(t_data *data);
void	env_unset(t_data *data);
void	env_free(t_env *node);
int		env_lstsize(t_data *data);

//	*-> Token Functions
t_token	*token_last(t_data *data);
void	token_delone(t_token **node);
void	token_add(t_data *data, t_token **head, int start, int len);
void	token_tolst(t_data *data, t_token **head, unsigned int start);
void	token_lstclear(t_data *data);
void	token_merge(t_data *data);
void	token_reorder(t_data *data);
bool	token_validation(t_data *data);

// *-> AST Functions
void	ast_lstclear(t_data *data);
// AST Utils Functions
t_ast	*new_ast(t_token *token);
t_ast	*ast_mem_allocate(t_ast **new_node);
t_ast	*set_ast_defaults(t_ast *ast);
void	add_left_ast(t_ast *ast, t_ast *new_node);
void	add_right_ast(t_ast *ast, t_ast *new_node);
// void	free_ast(t_ast *ast);
int		is_file(t_token *token);

// Execution Function
void	execution(t_data *data);
void	prepare_pipe(t_ast *new_node);
void	prep_heredocs(t_ast *ast, t_data *data);
void	wait_on_pids(t_data *data);
void	close_pipes(t_data *data);
void	close_files(t_data *data);
//	*-> redirections.c
int		check_for_redirs(t_ast *ast);
int		command_redirs(t_data *data, t_ast *ast);
//	*-> simple_cmd.c
int		simple_cmd(t_data *data);
int		pipe_cmd(t_data *data);
void	call_parent(pid_t pid, t_ast *ast, t_data *data);
void	call_child(char *cmd, t_ast *ast, t_data *data);
//	*-> str_join.c
char	*join_strs(char *str, char *buffer);
void	free_2dchar(char **str);
//	*-> cmd_utils.c
int		check_for_sleep(int pid, t_ast *ast, int last);
char	*get_cmd_path(char *cmd, t_data *data);
void	prep_command_execution(pid_t pid, t_data *data, t_ast *ast, char *path);
//	*-> pipe_utils.c
int		is_first_pipe(t_ast *ast);
int		is_last_pipe(t_ast *ast);
//	*->redir_utils.c
int		in_exists(t_ast *ast);
int		out_exists(t_ast *ast);

// Builtins Functions
void	builtins(t_data *data);
void	builtins_with_out(t_data *data);
void	cd(t_data *data);
void	echo(t_data *data);
void	env(t_data *data);
void	exit_shell(t_data *data);
void	export(t_data *data);
void	pwd(t_data *data);

// ***** Execution Utils Functions ***** //
bool	is_builtin(t_data *data);
bool	is_builtin_with_out(t_data *data);

// ***** Main Utils Functions ***** //
//	*-> data.c
void	data_init(t_data *data, char **env);
void	data_status(t_data *data, int exit_status);
void	data_reset(t_data *data);
void	data_free(t_data *data);

//	*-> errors
void	syntax_error(t_data *data, char *err);
void	print_error(char *err_name, char *err);

//	*-> free.c
void	free_ast(t_ast *ast);
void	free_data(t_data *data);

//	*-> init.c
void	init_data(t_data *data, char **env);

//	*-> utils.c
bool	is_redirect(t_token *token);
void	set_data_init_null(t_data *data);
bool	is_quotes(t_token *token);
bool	is_token_mergeable(t_token *token);
void	reset_tokens_index(t_data *data);

#endif
