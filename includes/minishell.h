/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:43:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/16 19:19:56 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WHITESPACES " \t\v\f\r"

// echo hi > file1 > file2 > file3 hello how are we > file4 hi | ls -la | ls>file5 -la
// echo hi >"file1     iknj jnjnj kmk'''''''><><><><>>>>>>>" >file2 > file3 hello how are we >file4 hi | ls -la | ls>file5 -la

// (ls) || echo

// typedef struct s_redirection
// {
// 	char *file;// 0 file1 1 file2
// 	int type; // 0 IN_FILE 1 IN_FILE
// }	t_redirection;

// typedef struct s_cmd
// {
// 	t_redirection	*redirection; //4
// 	int num_of_redirections;
// 	char **cmd;
// }	t_cmd;

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

// Token Utils Functions
// t_token	*new_token(t_data *data, int start, int len);
// t_token	*add_token(t_token **head, t_token *new_token);
// void	free_tokens(t_token *tokens);
t_token	*create_tokens(t_data *data);

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
void	free_env_list(t_env *env_list);
// void	free_env(char **env);
// void	free_path(t_env *path);
void	free_tokens(t_token *tokens);
void	free_ast(t_ast *ast);
void	free_data(t_data *data);
void	exit_success(t_data *data);
void	exit_failure(t_data *data);

// DELETE ME
void	print_env_list(t_env *lst);
void	print_tokens(t_token *lst);
void	print_ast(t_ast *ast);
void	print_path(char **path);

#endif
