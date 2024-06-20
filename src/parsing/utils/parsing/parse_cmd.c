/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:43:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/20 18:39:48 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_next_valid_token_words(t_token *token)
{
	bool	first;
	char	*args;
	char	*temp;

	args = NULL;
	first = true;
	while (token && token->type <= TOKEN_WORD)
	{
		if (first)
		{
			args = ft_strjoin(token->value, NULL);
			first = false;
		}
		else if (token->type == TOKEN_WORD && !is_file(token))
		{
			temp = args;
			args = ft_strjoin(temp, " ");
			free(temp);
			temp = args;
			args = ft_strjoin(temp, token->value);
			free(temp);
			token->is_parsed = true;
		}
		token = token->next;
	}
	return (args);
}

static void	check_redir_tokens(t_token *token, t_ast *right_node)
{
	t_token	*next;
	t_token	*prev;
	char	*args;

	next = token->next;
	prev = token->prev;
	right_node->type = NODE_WORD;
	args = join_next_valid_token_words(token);
	right_node->cmd = ft_split(args, ' ');
	right_node->token = token;
	if (prev && is_file(prev))
		check_left_for_redir(prev->prev, right_node);
	if (next && is_file(next->next))
		check_right_for_redir(next, right_node);
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
