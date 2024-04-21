/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:43:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 14:33:46 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "bash$ "
# define ERR_PROMPT "bash: "
# define WHITESPACES " \t\v\f\r"

# define SYNTAX_ERR "syntax error near unexpected token"

enum
{
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_PIPE,
	TOKEN_WORD
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
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_data
{
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
bool	token_validation(t_data *data);
int		token_type(char *token);



// Enviornment Utils Functions
// t_env	*env_to_list(t_data *data);
// char	**list_to_env(t_data *data);
// t_env	*get_env_node(t_data *data, char *key);

// AST Utils Functions
t_ast	*new_ast(int type);
void	add_ast(t_ast **ast, t_ast *new_node);
// void	free_ast(t_ast *ast);

// Execution Function
void	execution(t_data *data);

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

// DELETE ME
void	print_env_array(char **env);
void	print_env_list(t_env *lst);
void	print_tokens(t_token *lst);
void	print_ast(t_ast *ast);
void	print_path(char **path);

#endif
