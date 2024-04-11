/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:43:00 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/11 19:53:37 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}   t_env;

typedef struct s_history
{
	char			    *line;
	struct s_history	*next;
	struct s_history	*prev;
	struct s_history	*head;
	struct s_history	*current;
}   t_history;

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}   t_token;

typedef struct s_ast
{
	char			*data;
	int				type;
	struct s_ast	*left;
	struct s_ast	*right;
}   t_ast;

typedef struct s_data
{
	char			*line;
	char			**env;
	char			**av;
	int				exit_status;
	t_env			*env_list;
	t_env			*path;
	t_history		*history;
	t_token			*tokens;
	t_ast			*ast;
}   t_data;

// Enviornment Utils Functions
t_env	*env_to_list(char **env);
char	**list_to_env(t_env *env_list);
t_env	*get_path(t_env *env_list);
void	free_env_list(t_env *env_list);
void	free_env(char **env);


// History Utils Functions
t_history	*init_history(t_history *history);

void    print_env_list(t_env *lst);

#endif
