/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:03:47 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/05 15:47:21 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_redir_out(t_token *token, t_ast *new_node)
{
	new_node->type = NODE_REDIR;
	if (token->type == TOKEN_APPEND)
	{
	ft_putstr_fd("		PREPARING APPEND\n", 2);
		new_node->redir_append->exists = true;
		new_node->redir_append->file = token->next->value;
	}
	else if (token->type == TOKEN_REDIR_OUT)
	{
	ft_putstr_fd("		PREPARING REDIR OUT\n", 2);
		new_node->redir_out->exists = true;
		new_node->redir_out->file = token->next->value;
	}
	token->next->is_parsed = true;
	token = token->next->next;
}

static void	parse_redir_in(t_token *token, t_ast *new_node)
{
	new_node->type = NODE_REDIR;
	if (token->type == TOKEN_REDIR_IN)
	{
	ft_putstr_fd("		PREPARING REDIR IN\n", 2);
		new_node->redir_in->exists = true;
		new_node->redir_in->file = token->next->value;
	}
	else if (token->type == TOKEN_HEREDOC)
	{
	ft_putstr_fd("		PREPARING HEREDOC\n", 2);
		new_node->heredoc->exists = true;
		new_node->heredoc->stop_key = token->next->value;
	}
	token->next->is_parsed = true;
	token = token->next->next;
}

static void	create_redir_ast_attached(t_token *token, t_ast *node)
{
	t_ast	*attach_to;
	t_ast	*new_node;

	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node || !ast_mem_allocate(&new_node))
		return ;
	set_ast_defaults(new_node);
	ft_putstr_fd(token->value, 2);
	ft_putstr_fd("\n", 2);
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_HEREDOC)
		parse_redir_in(token, new_node);
	else if (token->type == TOKEN_REDIR_OUT || token->type == TOKEN_APPEND)
		parse_redir_out(token, new_node);
	attach_to = node;
	while (attach_to->right)
		attach_to = attach_to->right;
	attach_to->right = new_node;
	new_node->head = attach_to;
}

void	check_left_for_redir(t_token *token, t_ast *node)
{
	while (token && !token->is_parsed)
	{
		token->is_parsed = true;
		if (token->prev && is_file(token))
			create_redir_ast_attached(token->prev, node);
		else
		{
			node->type = -1;
			ft_putstr_fd("minishell: syntax error near unexpected token\
			 `newline'", 2);
			node->type = NODE_WORD;
			break ;
		}
		token = token->prev->prev;
	}
}

void	check_right_for_redir(t_token *token, t_ast *node)
{
	while (token && !token->is_parsed)
	{
		token->is_parsed = true;
		if (token->next && is_file(token->next))
			create_redir_ast_attached(token, node);
		else
		{
			node->type = -1;
			ft_putstr_fd("minishell: syntax error near unexpected token\
			 `newline'", 2);
			node->type = NODE_WORD;
			break ;
		}
		token = token->next->next;
	}
}
