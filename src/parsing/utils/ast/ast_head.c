/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_head.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:21:18 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 07:25:09 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static t_token	*token_get(t_data *data, t_token *head_node, char direction);
t_ast			*ast_head(t_data *data, t_token *token, char direction);

/// @brief Used to get the head of the ast node
/// @param data The main struct
/// @param head_node The head node of the ast
/// @param direction The direction to search for the head node
/// @return The head node of the ast
static t_token	*token_get(t_data *data, t_token *head_node, char direction)
{
	t_token	*match;

	match = NULL;
	while (head_node)
	{
		if (direction == 'l')
		{
			if (head_node->type == data->left_high_token)
				match = head_node;
			if (match)
				break ;
			head_node = head_node->prev;
		}
		else
		{
			if (head_node->type == data->right_high_token)
				match = head_node;
			head_node = head_node->next;
		}
	}
	return (match);
}

/**
 * The purpose of this function is to get the token
 * The direction parameter is used to determine which side to go left or right
 * The function first checks if the direction is 'l' or 'r'
 * If the direction is 'l', the head_node we check is the previous node
 * If the direction is 'r', the head_node we check is the next node
 * The match variable is used to store the found token
 * assume a line with a multiple pipes,
 * the last pipe will be the head of the tree,
 * so the match variable will store a pipe at time, till we reach the last token
 * Then the pipe we want is the last pipe stored in the match variable
 * 
 * The next time we will call this function to set the left or right as nodes
 * we will call it with token_head->prev or token_head->next
 * so we skip the pipe we already took as the head of the tree
 * 
 * if (direction == 'l') && (match) we break out,
 * because we are moving from right to left so highest precedence token 
 * will be the first one we meet not the last one as we move from left to right
*/

/// @brief Used to get the head of the ast node
/// @param data The main struct
/// @param token The token to search for the head node
/// @param direction The direction to search for the head node
/// @return The head node of the ast
t_ast	*ast_head(t_data *data, t_token *token, char direction)
{
	t_token	*node;
	int		token_value;

	node = NULL;
	if (direction == 'l')
		token_value = data->left_high_token;
	else
		token_value = data->right_high_token;
	while (token_value >= 0)
	{
		node = token_get(data, token, direction);
		if (node)
			break ;
		if (direction == 'l')
		{
			data->left_high_token--;
			token_value = data->left_high_token;
		}
		else
		{
			data->right_high_token--;
			token_value = data->right_high_token;
		}
	}
	return (ast_new(data, node));
}

/**
 * The purpose of this function is to get the head of the ast node
 * The direction parameter is used to determine which side to go left or right
 * The function first checks if the direction is 'l' or 'r'
 * and then gets the token value from the left_high_token or right_high_token
 * The function then calls token_get to get the token
 * If the token is found, the function breaks the loop
 * If the direction is 'l', the left_high_token is decremented
 * If the direction is 'r', the right_high_token is decremented
 * The function then returns the new ast node with the found token
*/
