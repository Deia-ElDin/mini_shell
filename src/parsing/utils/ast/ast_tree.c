/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/20 15:18:42 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	t_ast	*node_values(t_data *data, t_ast *new_node, t_token *token)
// {
// 	new_node->type = token->type;
// 	if (new_node->type == CMD)
// 	{
// 		new_node->cmd = ft_split(token->value, ' ');
// 		if (!new_node->cmd)
// 			return (data_status(data, 1), NULL);
// 	}
// 	else
// 		new_node->cmd = NULL;
// 	new_node->left = NULL;
// 	new_node->right = NULL;
// 	new_node->token = token;
// 	return (new_node);
// }

// static t_ast	*ast_new(t_data *data, t_token *token)
// {
// 	t_ast	*new_node;

// 	if (!data || !token)
// 		return (NULL);
// 	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
// 	if (!new_node)
// 		return (data_status(data, 1), NULL);
// 	return (node_values(data, new_node, token));
// }

// void	ast_tree(t_data *data, t_token *token)
// {
// 	t_ast	*new_node;

// 	new_node = ast_new(data, token);
// 	if (!new_node)
// 		return (data_status(data, 1));
// 	if (!data->ast)
// 		data->ast = new_node;
// 	else if (token->type == CMD)
// 	{
// 		if (!data->ast->left && token->next && token->next->next)
// 			data->ast->left = new_node;
// 		else if (!data->ast->right)
// 			data->ast->right = new_node;
// 	}
// 	else
// 	{
// 		new_node->left = data->ast;
// 		data->ast = new_node;
// 	}
// }

// t_ast	*ast_new(t_data *data, t_token *token)
// {
// 	t_ast	*new_node;

// 	if (!data || !token)
// 		return (NULL);
// 	new_node = (t_ast *)calloc(1, sizeof(t_ast));
// 	if (!new_node)
// 		return (data_status(data, 1), NULL);
// 	new_node->type = token->type;
// 	if (new_node->type == CMD)
// 	{
// 		new_node->cmd = ft_split(token->value, ' ');
// 		if (!new_node->cmd)
// 			return (data_status(data, 1), NULL);
// 	}
// 	else
// 		new_node->cmd = NULL;
// 	new_node->left = NULL;
// 	new_node->right = NULL;
// 	new_node->token = token;
// 	return (new_node);
// }

// void	ast_tree(t_data *data, t_token *token)
// {
// 	t_ast *new_node;

//     if (!data || !token)
//         return;
//     new_node = ast_new(data, token);
//     if (!new_node)
//         return (data_status(data, 1));
//     if (!data->ast)
//         data->ast = new_node;
//     else
//     {
//         if (token->type == PIPE)
//             handle_pipe(data, new_node);
//         else if (token->type == REDIR_IN || token->type == REDIR_OUT || token->type == HEREDOC || token->type == APPEND)
//             handle_redirection(data, new_node);
//         else if (token->type == CMD || token->type == BUILTIN)
//             handle_command(data, new_node);
//     }
// }

// void handle_pipe(t_data *data, t_ast *new_node)
// {
//     t_ast *current = data->ast;

//     while (current->type == PIPE)
//         current = current->right;

//     new_node->left = current;
//     data->ast = new_node;
// }

// void handle_redirection(t_data *data, t_ast *new_node)
// {
//     t_ast *current = data->ast;

//     while (current->right && (current->right->type == CMD || current->right->type == BUILTIN))
//         current = current->right;

//     current->right = new_node;
// }

// void handle_command(t_data *data, t_ast *new_node)
// {
//     t_ast *current = data->ast;

//     while (current->right)
//         current = current->right;

//     current->right = new_node;
// }