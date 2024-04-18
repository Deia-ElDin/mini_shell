/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:02:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/18 02:52:14 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_list(t_env **env_list)
{
	t_env	*crnt_node;
	t_env	*next_node;

	if (!env_list || !*env_list)
		return ;
	crnt_node = *env_list;
	while (crnt_node)
	{
		next_node = crnt_node->next;
		free(crnt_node->key);
		free(crnt_node);
		crnt_node = next_node;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*crnt_token;
	t_token	*next_token;

	if (!tokens || !*tokens)
		return ;
	crnt_token = *tokens;
	while (crnt_token)
	{
		next_token = crnt_token->next;
		free(crnt_token->value);
		free(crnt_token);
		crnt_token = next_token;
	}
	*tokens = NULL;
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

void	free_ptr(char **ptr)
{
	if (!ptr || !*ptr)
		return ;
	free(*ptr);
	*ptr = NULL;
}

void	free_arr(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;

}

void	free_data(t_data *data)
{
	printf("\n\nfree_data\n\n");
	free_env_list(&data->env_list);
	ft_free(&data->env, 'a');
	ft_free(&data->path, 'a');
	if (data->tokens)
		free_tokens(&data->tokens);
	// free_ast(data->ast);
	ft_free(&data->line, 'p');
}
