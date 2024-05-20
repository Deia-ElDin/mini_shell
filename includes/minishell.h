/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:43:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/20 15:20:03 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define PROMPT "mini-shell$ "
# define ERR_PROMPT "mini-shell: "
# define WHITESPACES " \t\v\f\r"

# define SYNTAX_ERR "syntax error near unexpected token"

enum
{
	NODE_CMD,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_HEREDOC,
	NODE_APPEND,
	NODE_PIPE,
	NODE_BUILTIN,
	NODE_SINGLE_QUOTE,
	NODE_DOUBLE_QUOTE,
	NODE_AND,
	NODE_OR,
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
	bool			is_space;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	int				type;
	char			**cmd;
	char			*infile;
	char			*outfile;
	int				append;
	int				here_doc;
	int				pipe;
	struct s_ast	*left;
	struct s_ast	*right;
	t_token			*token;
}	t_ast;

typedef struct s_data
{
	// int				highest_token;
	// int				left_high_token;
	// int				right_high_token;
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
bool	parser(t_data *data);

// ***** Parsing Utils Functions ***** //

//	*-> Env Functions
t_env	*env_get(t_data *data, char *key);
t_env	*env_last(t_data *data);
char	*env_expansion(t_data *data, char *str);
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
void	token_lstclear(t_data *data);
void	token_add(t_data *data, t_token **head, int start, int len);
void	token_tolst(t_data *data, t_token **head, unsigned int start);
void	token_merge(t_data *data);
void	token_merge(t_data *data);
bool	token_validation(t_data *data);

// *-> AST Functions
void	ast_lstclear(t_data *data);
void	ast_tree(t_data *data, t_token *token);

// Execution Function
void	execution(t_data *data);

// Builtins Functions
void	builtins(t_data *data);
void	cd(t_data *data);
void	echo(t_data *data);
void	env(t_data *data);
void	exit_shell(t_data *data);
void	export(t_data *data);
void	pwd(t_data *data);

// ***** Execution Utils Functions ***** //
bool	is_builtin(t_data *data);

// ***** Main Utils Functions ***** //
//	*-> data.c
void	data_init(t_data *data, char **env);
void	data_status(t_data *data, int exit_status);
void	data_reset(t_data *data);
void	data_free(t_data *data);

//	*-> errors
void	syntax_error(char *err);
void	export_err(t_data *data, char *err);

//	*-> exit.c
void	exit_success(t_data *data);
void	exit_failure(t_data *data);

// DELETE ME
void	print_env_array(char **env);
void	print_env_list(t_env *lst);
void	print_tokens(t_token *lst);
void	print_ast(t_ast *ast);
void	print_path(char **path);

#endif
