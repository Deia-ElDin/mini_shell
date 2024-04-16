/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:02:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/16 16:27:07 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	if (!env_list)
		return ;
	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->key);
		free(tmp);
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return ;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

// void	free_path(t_env *path)
// {
// 	if (!path)
// 		return ;
// 	if (path->next)
// 		free(path->key);
// 	if (path->value)
// 		free(path->value);
// 	free(path);
// }

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	free(ast);
}

void	free_data(t_data *data)
{
	free_env_list(data->env_list);
	ft_free(&(data->env), 'a');
	ft_free(&(data->path), 'a');
	free_tokens(data->tokens);
	free_ast(data->ast);
	if (data->line)
		free(data->line);
}
