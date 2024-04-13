/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:43:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/13 14:29:31 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TOKENS "|;&()<>"

enum
{
	TOKEN_QUOTE = 1,
	TOKEN_ESCAPE = 2,
	TOKEN_REDIR_IN = 3,
	TOKEN_REDIR_OUT = 4,
	TOKEN_DOUBLE_REDIR_IN = 5,
	TOKEN_DOUBLE_REDIR_OUT = 6,
	TOKEN_PIPE = 7,
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
	int				token;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_cmd
{
	char			**av;
	char			*cmd;
	int				number_of_available_arguments;
	int				number_of_arguments;
}	t_cmd;

typedef struct s_data
{
	char			*line;
	char			**env;
	char			**av;
	int				exit_status;
	t_env			*env_list;
	t_env			*path;
	// t_history		*history;
	t_token			*tokens;
	t_ast			*ast;
}	t_data;


// Parsing Function
void	parsing(t_data *data);

// Lexer Functions
t_token	*lexer(char *line);

// Token Utils Functions
t_token	*new_token(int type, char *line);
t_token	*add_token(t_token **head, t_token *new_token);

// Data Utils Functions
void	init_data(t_data *data);
void	set_data(t_data *data, char **env, char **av);
void	free_data(t_data *data);

// Enviornment Utils Functions
t_env	*env_to_list(char **env);
char	**list_to_env(t_env *env_list);
t_env	*get_path(t_env *env_list);
void	free_env_list(t_env *env_list);
void	free_env(char **env);

// History Utils Functions
// t_history	*init_history(t_history *history);

// Execution Function
void	execution(t_data *data);

// Builtins Functions
void	builtins(t_data *data);
void	cd(t_data *data);
// void    echo(t_data *data);
// void    env(t_data *data);
// void    exit_shell(t_data *data);
// void    export(t_data *data);
// void    pwd(t_data *data);
// void    unset(t_data *data);




// DELETE ME
void	print_env_list(t_env *lst);
void	print_tokens(t_token *lst);

#endif
