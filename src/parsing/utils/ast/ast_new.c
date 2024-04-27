/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:03:03 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 07:24:00 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// t_ast	*cmd_node(t_data *data, t_ast *node, t_token *token)
// {
// 	node->cmd = ft_strdup(token->value);
// 	if (!node->cmd)
// 		exit_failure(data);
// 	return (node);
// }

// t_ast	*special_node(t_data *data, t_ast *node, t_token *token)
// {
// 	node->cmd = NULL;
// 	if (token->type == TOKEN_WORD)
// 	{
// 		node->args = ft_strdup(token->value);
// 		if (!node->args)
// 			exit_failure(data);
// 	}
// 	else
// 		node->args = NULL;
// 	node->file = NULL;
// 	return (node);
// }

t_ast	*ast_new(t_data *data, t_token *token)
{
	t_ast	*new_node;

	if (!data || !token)
		return (NULL);
	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		exit_failure(data);
	new_node->type = token->type;
	new_node->index = token->index;
	// if (token->type == TOKEN_WORD)
	// {
	// 	new_node->cmd = ft_strdup(token->value);
	// 	if (!new_node->cmd)
	// 		exit_failure(data);
	// }
	// else
	// 	new_node->cmd = NULL;
	// new_node->args = NULL;
	new_node->file = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->token = token;
	return (new_node);
}
