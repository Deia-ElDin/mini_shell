/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:43:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/01 15:41:13 by melshafi         ###   ########.fr       */
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
	NODE_WORD,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_HEREDOC,
	NODE_APPEND,
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
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_OR,
	TOKEN_AND
};

/*



echo
/usr/bin/echo

echo hello world

"echo" "hello" "world" NULL
*/

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
	bool			is_taken;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	int				type;
	char			**cmd;
	char			*file;
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

// ***** Parsing Utils Functions ***** //

//	*-> Env Functions
t_env	*env_new(t_data *data, char *env);
t_env	*env_update(t_data *data, char *env);
t_env	*env_get(t_data *data, char *key);
t_env	*env_last(t_data *data);
char	*env_expansion(t_data *data, char *str);
void	env_add(t_data *data, t_env *new);
void	env_tolst(t_data *data);
void	env_toarr(t_data *data);
void	env_lstclear(t_data *data);
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
// AST Utils Functions
t_ast	*new_ast(int type);
void	add_left_ast(t_ast *ast, t_ast *new_node);
void	add_right_ast(t_ast *ast, t_ast *new_node);

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

// ***** Main Utils Functions ***** //
//	*-> data.c
void	data_init(t_data *data, char **env);
void	data_reset(t_data *data);
void	data_free(t_data *data);

//	*-> error.c
void	syntax_error(char *err);

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
