/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:02:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 19:04:36 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	env_clear(data);
	token_clear(data);
	ft_free(&data->env, 'a');
	ft_free(&data->path, 'a');
	free_ast(data->ast);
	ft_free(&data->line, 'p');
}
