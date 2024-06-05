/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:43:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/05 11:18:36 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parse_redir_type(t_token *next, t_ast *right_node)
{
	right_node->type = NODE_REDIR;
	if (next->type == TOKEN_APPEND)
	{
		right_node->redir_in->exists = false;
		right_node->redir_append->exists = true;
		right_node->redir_append->file = next->next->value;
	}
	else if (next->type == TOKEN_REDIR_OUT)
	{
		right_node->redir_append->exists = false;
		right_node->redir_out->exists = true;
		right_node->redir_out->file = next->next->value;
	}
	if (next->type == TOKEN_REDIR_IN)
	{
		right_node->heredoc->exists = false;
		right_node->redir_in->exists = true;
		right_node->redir_in->file = next->next->value;
	}
	else if (next->type == TOKEN_HEREDOC)
	{
		right_node->redir_in->exists = false;
		right_node->heredoc->exists = true;
		right_node->heredoc->stop_key = next->next->value;
	}
	next->next->is_parsed = true;
	next = next->next->next;
}

static void	check_redir_tokens(t_token *token, t_ast *right_node)
{
	t_token	*next;
	int		redir_token;

	next = token->next;
	redir_token = TOKEN_REDIR_IN;
	if (!next || next->type > TOKEN_HEREDOC)
		right_node->type = NODE_WORD;
	right_node->cmd = ft_split(token->value, ' ');
	right_node->token = token;
	while (redir_token >= TOKEN_REDIR_OUT)
	{
		while (next && !next->is_parsed && (next->type == redir_token || next->type == redir_token + 1))
		{
			next->is_parsed = true;
			if (next->next)
				parse_redir_type(next, right_node);
			else
			{
				right_node->type = -1;
				ft_putstr_fd("minishell: syntax error near unexpected token\
				 `newline'", 2);
				right_node->type = NODE_WORD;
				break ;
			}
		}
		next = token->next;
		redir_token -= 2;
	}
}

t_ast	*parse_cmd(t_token *token, t_ast *new_node)
{
	t_ast	*left_node;
	t_ast	*right_node;

	left_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	right_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!left_node || !right_node)
		exit(1);
	set_ast_defaults(left_node);
	set_ast_defaults(right_node);
	if (!ast_mem_allocate(&left_node) || !ast_mem_allocate(&right_node))
		return (NULL);
	check_redir_tokens(token, right_node);
	right_node->head = new_node;
	left_node->type = NODE_WORD;
	left_node->cmd = (char **)ft_calloc(2, sizeof(char *));
	if (!left_node->cmd)
		return (NULL);
	left_node->cmd[0] = ft_strdup(right_node->cmd[0]);
	left_node->cmd[1] = NULL;
	left_node->head = new_node;
	new_node->left = left_node;
	new_node->right = right_node;
	return (new_node);
}

int	is_file(t_token *token)
{
	if (token->type != TOKEN_WORD)
		return (0);
	else if (token->prev && token->prev->type < TOKEN_WORD)
		return (1);
	else
		return (0);
}
