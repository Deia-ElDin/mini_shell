/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:27:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/01 17:37:20 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*get_next_left_node(t_token *tokens)
{
	t_token	*token_node;
	t_token	*nav_token;
	int		next_high_token;

	next_high_token = TOKEN_AND;
	nav_token = NULL;
	token_node = NULL;
	while (next_high_token >= 0)
	{
		nav_token = tokens;
		while (nav_token)
		{
			printf("Inside get next left NHT(%d) CT(%d)\n", next_high_token, nav_token->type);
			if (nav_token->type == next_high_token)
				token_node = nav_token;
			nav_token = nav_token->prev;
		}
		if (!token_node)
			next_high_token--;
		else
			break ;
	}
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
	while (next_high_token >= 0)
	{
		nav_token = tokens;
		while (nav_token)
		{
			printf("Inside get next left NHT(%d) CT(%d)\n", next_high_token, nav_token->type);
			if (nav_token->type == next_high_token)
				token_node = nav_token;
			nav_token = nav_token->next;
		}
		if (!token_node)
			next_high_token--;
		else
			break ;
	}
	return (token_node);
}

static int	recursive_parsing(t_data *data, t_token *token, t_ast *node)
{
	t_ast	*new_node;
	t_token	*new_token;

	printf("Inside recur pars\n");
	new_token = NULL;
	if (!token)
		return (1);
	if (token->prev)
	{
		token->prev->next = NULL;
		new_token = token->prev;
		token->prev = NULL;
	}
	new_token = get_next_left_node(new_token);
	if (new_token)
	{
		new_node = new_ast(new_token->type);
		printf("New Token Type: (%d)\n", new_token->type);
	}
	if (new_node)
		add_left_ast(node, new_node);
	if (new_node && new_token && recursive_parsing(data, new_token, new_node) && token->prev)
		return (token_delone(&token), 1);
	printf("checking right\n");
	if (token->next)
	{
		token->next->prev = NULL;
		new_token = token->prev;
		token->next = NULL;
	}
	new_token = get_next_right_node(new_token);
	if (new_token)
	{
		new_node = new_ast(new_token->type);
		printf("New Token Type: (%d)\n", new_token->type);
	}
	if (new_node)
		add_right_ast(node, new_node);
	if (new_node && new_token && recursive_parsing(data, new_token, new_node) && token->next)
		return (token_delone(&token), 1);
	return (token_delone(&token), 0);
}

t_ast	*parser(t_data *data)
{
	t_ast	*head_node;
	t_token	*head_token;

	if (!data)
		return (NULL);
	head_token = get_next_right_node(data->tokens);
	head_node = NULL;
	if (head_token)
	{
		printf("About to create head node\n");
		head_node = new_ast(head_token->type);
	}
	printf("About to check recursive parsing\n");
	if (!head_node)
		return (printf("headnode is fucked\n"), head_node);
	recursive_parsing(data, head_token, head_node);
	return (head_node);
}

/*


echo hello | tr e a

|

echo




*/
