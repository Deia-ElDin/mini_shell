/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:28:40 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 04:38:32 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ast_add(t_data *data, t_ast *head, char direction);

/// @brief Used to add the left and right nodes to the head node
/// @param data The main struct
/// @param head The head node
/// @param direction The direction to add the node to
void	ast_add(t_data *data, t_ast *head, char direction)
{
	if (direction == 'l')
	{
		head->left = ast_head(data, head->token->prev, 'l');
		if (!head->left || data->left_high_token == 0)
			return ;
		ast_add(data, head->left, 'l');
		ast_add(data, head->left, 'r');
	}
	else
	{
		head->right = ast_head(data, head->token->next, 'r');
		if (!head->right || data->right_high_token == 0)
			return ;
		ast_add(data, head->right, 'l');
		ast_add(data, head->right, 'r');
	}
}

/**
 * The direction parameter is used to determine which side of the head node 
 * to add the node to
 * If the direction is 'l', the node is added to the left side of the head node
 * If the direction is 'r', the node is added to the right side of the head node
 * The function first checks if the direction is 'l' or 'r'
 * and then adds the node to the left or right side of the head node respectively
 * The function then checks if the left or right node is NULL
 * or if left_high_token or right_high_token is 0
 * If any of that, the function returns
 * Else it calls itself recursively with the left or right node respectively
 
 * The purpose of left_high_token & right_high_token is:
 * assume there's aan && which will be the head node,
 * assume there's a pipe on the left side and also on the right side,
 * if we had one value which holds the highest precedence token,
 * it will go below the pipe on the left side,
 * yet still there's a pipe on the right side,
 * to avoid this, we have two values,
 * one for the left side and one for the right side
*/
