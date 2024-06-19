/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/19 16:13:02 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static t_token	*get_head_node(t_token *tokens)
{
	t_token	*token_node;
	t_token	*nav_token;
	int		next_high_token;

	next_high_token = TOKEN_AND;
	nav_token = NULL;
	token_node = NULL;
	while (next_high_token >= TOKEN_WORD)
	{
		nav_token = tokens;
		while (nav_token && !nav_token->is_parsed && !is_file(nav_token))
		{
			if (nav_token->type == next_high_token)
				token_node = nav_token;
			nav_token = nav_token->next;
		}
		if (!token_node)
			next_high_token--;
		else
			break ;
	}
	if (token_node)
		token_node->is_parsed = true;
	return (token_node);
}

static t_token	*get_next_left_node(t_token *tokens)
{
	t_token	*token_node;
	t_token	*nav_token;
	int		next_high_token;

	next_high_token = TOKEN_AND;
	nav_token = NULL;
	token_node = NULL;
	while (next_high_token >= TOKEN_WORD)
	{
		nav_token = tokens->prev;
		while (nav_token && !nav_token->is_parsed && !is_file(nav_token))
		{
			if (nav_token->type == next_high_token)
			{
				token_node = nav_token;
				break ;
			}
			nav_token = nav_token->prev;
		}
		if (!token_node)
			next_high_token--;
		else
			break ;
	}
	if (token_node)
		token_node->is_parsed = true;
	return (token_node);
}

/*
Find next highest token in the precedence and returns next head token
*/
static t_token	*get_next_right_node(t_token *tokens)
{
	t_token	*token_node;
	t_token	*nav_token;
	int		next_high_token;

	next_high_token = TOKEN_AND;
	nav_token = NULL;
	token_node = NULL;
	while (next_high_token >= TOKEN_WORD)
	{
		nav_token = tokens->next;
		while (nav_token && !nav_token->is_parsed && !is_file(nav_token))
		{
			if (nav_token->type == next_high_token)
			{
				token_node = nav_token;
				break ;
			}
			nav_token = nav_token->next;
		}
		if (!token_node)
			next_high_token--;
		else
			break ;
	}
	if (token_node)
		token_node->is_parsed = true;
	return (token_node);
}

static int	recursive_parsing(t_data *data, t_token *token, t_ast *node)
{
	t_ast	*new_node;
	t_token	*new_token;

	new_token = NULL;
	new_node = NULL;
	if (!token)
		return (1);
	new_token = get_next_left_node(token);
	if (new_token)
		new_node = new_ast(new_token);
	if (new_node)
		add_left_ast(node, new_node);
	if (new_node && new_token && recursive_parsing(data, new_token, new_node))
		return (1);
	new_token = get_next_right_node(token);
	if (new_token)
		new_node = new_ast(new_token);
	if (new_node)
		add_right_ast(node, new_node);
	if (new_node && new_token && recursive_parsing(data, new_token, new_node))
		return (1);
	return (0);
}

t_ast	*parser(t_data *data)
{
	t_ast	*head_node;
	t_token	*head_token;

	data->ast = NULL;
	if (!data)
		return (NULL);
	head_token = get_head_node(data->tokens);
	head_node = NULL;
	if (head_token)
		head_node = new_ast(head_token);
	else
		return (print_error(NULL, "command not found"), NULL);
	if (!head_node)
		return (head_node);
	recursive_parsing(data, head_token, head_node);
	data->ast = head_node;
	while (head_node->right)
		head_node = head_node->right;
	head_node->end_flag = 1;
	return (head_node);
}
