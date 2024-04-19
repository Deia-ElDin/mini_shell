/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:43:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/19 20:44:16 by dehamad          ###   ########.fr       */
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

# define PIPE_ERR "syntax error near unexpected token `|'\n"
# define QUOTES_ERR "syntax error unclosed quotes\n"
# define REDIR_ERR "syntax error near unexpected token `newline'\n"

enum
{
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_ESCAPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_PIPE,
	TOKEN_SEMIC,
	TOKEN_WORD
};

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// typedef struct s_history
// {
// 	char				*line;
// 	struct s_history	*next;
// 	struct s_history	*prev;
// 	struct s_history	*head;
// 	struct s_history	*current;
// }	t_history;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}	t_token;

// Abstract Syntax Tree
typedef struct s_ast
{
	int				type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

// typedef struct s_cmd
// {
// 	char			**av;
// 	char			*cmd;
// 	int				number_of_available_arguments;
// 	int				number_of_arguments;
// }	t_cmd;

typedef struct s_data
{
	// int num_of_cmds;
	// t_cmd *cmds;
	char			*line;
	char			**env;
	// char			**av;
	char			**path;
	int				exit_status;
	t_env			*env_list;
	t_token			*tokens;
	t_ast			*ast;
}	t_data;


// Parsing Function
t_token	*lexer(t_data *data);
t_ast	*parser(t_data *data);

// Validation Functions
bool	validations(t_data *data);
// bool	validate_pipe(t_data *data);

// Validation Utils Functions
void	skip_spaces(char **line);
void	skip_word(char **line, char delimiter, bool *is_valid);

// Token Utils Functions
void	create_tokens(t_data *data, t_token **head, unsigned int start);

// Enviornment Utils Functions
t_env	*env_to_list(t_data *data);
char	**list_to_env(t_data *data);
t_env	*get_env(t_data *data, char *key);
// char	**get_env_value(t_data *data, char *key);
// void	free_env_list(t_env *env_list);
// void	free_env(char **env);

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
void	init_data(t_data *data, char **env);
void	free_env_list(t_env **env_list);
// void	free_env(char **env);
// void	free_path(t_env *path);
void	free_tokens(t_token **tokens);
void	free_ast(t_ast *ast);
void	free_data(t_data *data);
void	exit_success(t_data *data);
void	exit_failure(t_data *data);

// Error Functions
void	print_error(char *err);

// DELETE ME
void	print_env_list(t_env *lst);
void	print_tokens(t_token *lst);
void	print_ast(t_ast *ast);
void	print_path(char **path);

#endif
