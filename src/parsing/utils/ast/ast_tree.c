/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/19 18:30:33 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	t_ast	*node_values(t_data *data, t_ast *new_node, t_token *token)
{
	new_node->type = token->type - 2;
	if (token->type == TOKEN_WORD)
	{
		new_node->cmd = ft_split(token->value, ' ');
		if (!new_node->cmd)
			return (data_status(data, 1), NULL);
	}
	else
		new_node->cmd = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->token = token;
	token->is_taken = true;
	return (new_node);
}

static t_ast	*ast_new(t_data *data, t_token *token)
{
	t_ast	*new_node;

	if (!data || !token)
		return (NULL);
	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		exit_failure(data);
	return (node_values(data, new_node, token));
}

void	ast_tree(t_data *data, t_token *token)
{
	t_ast	*new_node;

	new_node = ast_new(data, token);
	if (!new_node)
		exit_failure(data);
	if (!data->ast)
		data->ast = new_node;
	else if (token->type == TOKEN_WORD)
	{
		if (!data->ast->left && token->next && token->next->next)
			data->ast->left = new_node;
		else if (!data->ast->right)
			data->ast->right = new_node;
	}
	else
	{
		new_node->left = data->ast;
		data->ast = new_node;
	}
}
