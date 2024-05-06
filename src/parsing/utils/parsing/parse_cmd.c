/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:43:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/06 17:04:42 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	check_redir_tokens(t_token *token, t_ast *right_node)
{
	if (token->prev && token->prev->type < TOKEN_WORD)
	{
		right_node->type = token->prev->type - 1;
		right_node->file = token->prev->value;
		right_node->cmd = ft_split(token->value, ' ');
	}
	else if (token->next && token->next->type < TOKEN_WORD)
	{
		right_node->type = token->next->type - 1;
		right_node->file = token->next->value;
		right_node->cmd = ft_split(token->value, ' ');
	}
	else
	{
		right_node->type = NODE_WORD;
		right_node->cmd = ft_split(token->value, ' ');
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
	check_redir_tokens(token, right_node);
	right_node->end_flag = 0;
	right_node->left = NULL;
	right_node->right = NULL;
	left_node->end_flag = 0;
	left_node->type = NODE_WORD;
	left_node->cmd = (char **)ft_calloc(2, sizeof(char *));
	if (!left_node->cmd)
		exit(1);
	left_node->cmd[0] = right_node->cmd[0];
	left_node->cmd[1] = NULL;
	left_node->left = NULL;
	left_node->right = NULL;
	new_node->left = left_node;
	new_node->right = right_node;
	return (new_node);
}
