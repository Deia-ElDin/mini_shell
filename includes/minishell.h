/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:43:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/24 14:31:51 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "bash$ "
# define ERR_PROMPT "bash: "
# define WHITESPACES " \t\v\f\r"

# define SYNTAX_ERR "syntax error near unexpected token"

enum
{
	NODE_WORD,
	NODE_CMD,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_HEREDOC,
	NODE_APPEND,
	NODE_PIPE,
	NODE_OR,
	NODE_AND
};

enum
{
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_WORD,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND
};

typedef struct s_env
{
	char			*key;
	char			*value;
	bool			is_equal;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	int		type;
	char	*cmd;
	char	*options;
	char	*args;
}	t_cmd;

typedef struct s_pipe
{
	int		type;
	int		*prev;
	int		*next;
}	t_pipe;

typedef struct s_redir
{
	int		type;
	char	*file;
}	t_redir;

typedef struct s_ast
{
	int				type;
	int				end_flag;
	char			*cmd;
	char			**args;
	char			*file;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_data
{
	int				file_fd;
	int				redirect_flag;
	int				saved_stdfds[2];
	int				pipe[2];
	int				next_high_token;
	char			*line;
	char			**env;
	// char			**av;
	char			**path;
	int				exit_status;
	t_env			*env_list;
	t_token			*tokens;
	t_ast			*ast;
}	t_data;

//  ************ Parsing Function ************  //
bool	lexer(t_data *data);
t_ast	*parser(t_data *data);

// Parsing Utils Functions
//	*-> Env Functions
t_env	*env_new(t_data *data, char *env);
t_env	*env_update(t_data *data, char *env);
t_env	*env_get(t_data *data, char *key);
t_env	*env_last(t_data *data);
char	*env_expansion(t_data *data, char *str);
void	env_add(t_data *data, t_env *new);
void	env_tolst(t_data *data);
void	env_toarr(t_data *data);
void	env_clear(t_data *data);
int		env_size(t_data *data);
//	*-> Token Functions
t_token	*token_new(t_data *data, unsigned int start, int len);
void	token_add(t_data *data, t_token **head, int start, int len);
void	token_tolst(t_data *data, t_token **head, unsigned int start);
void	token_clear(t_data *data);
void	token_del_relink(t_token **node);
bool	token_validation(t_data *data);
int		token_type(char *token);

// AST Utils Functions
t_ast	*new_ast(int type);
void	add_left_ast(t_ast *ast, t_ast *new_node);
void	add_right_ast(t_ast *ast, t_ast *new_node);
// void	free_ast(t_ast *ast);

// Execution Function
void	execution(t_data *data);
void	exec_ast(t_ast *ast, t_data *data);
//	*-> simple_cmd.c
int		simple_cmd(t_ast *ast_left, t_ast *ast_right, t_data *data);
int		pipe_cmd(t_data *data);

// Builtins Functions
void	builtins(t_data *data);
// void	cd(t_data *data);
// void	echo(t_data *data);
// void	env(t_data *data);
// void	exit_shell(t_data *data);
// void	export(t_data *data);
// void	pwd(t_data *data);
// void	unset(t_data *data);

// Utils Functions
//	*-> error.c
void	syntax_error(char *err);
void	print_error(char *err);
//	*-> exit.c
void	exit_success(t_data *data);
void	exit_failure(t_data *data);
//	*-> free.c
void	free_ast(t_ast *ast);
void	free_data(t_data *data);
//	*-> init.c
void	init_data(t_data *data, char **env);
//	*-> utils.c
void	skip_spaces(const char *line, int *i);
void	skip_quotes(const char *line, int *i);
//	*-> str_join.c
char	*join_strs(char *str, char *buffer);
void	free_2dchar(char **str);
//	*-> env_utils.c
char	*get_path(char **envp, char *cmd, char *var);
char	*get_all_paths(char **envp, char *var);
char	*get_cmd_path(char *cmd, t_data *data);
//	*->pipe_clean.c
char	*gnl_till_null(int *pipe_fd, char *str);
int		reset_fds(t_data *data);

// DELETE ME
void	print_env_array(char **env);
void	print_env_list(t_env *lst);
void	print_tokens(t_token *lst);
void	print_ast(t_ast *ast);
void	print_path(char **path);

#endif
