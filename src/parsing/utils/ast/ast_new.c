/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:03:03 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/28 19:50:38 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static	t_ast	*node_values(t_data *data, t_ast *new_node, t_token *token)
{
	char	*ptr;

	new_node->type = token->type;
	if (token->type == TOKEN_WORD)
	{
		ptr = ft_strdup(token->value);
		if (!ptr)
			exit_failure(data);
		new_node->cmd = ft_split(ptr, ' ');
		if (!new_node->cmd)
			exit_failure(data);
	}
	else
		new_node->cmd = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->token = token;
	token->is_taken = true;
	return (new_node);
}

t_ast	*ast_new(t_data *data, t_token *token)
{
	t_ast	*new_node;

	if (!data || !token)
		return (NULL);
	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		exit_failure(data);
	return (node_values(data, new_node, token));
}

	// if (token->type == TOKEN_WORD)
	// {
	// 	new_node->cmd = ft_strdup(token->value);
	// 	if (!new_node->cmd)
	// 		exit_failure(data);
	// }
	// else
	// 	new_node->cmd = NULL;
	// new_node->args = NULL;