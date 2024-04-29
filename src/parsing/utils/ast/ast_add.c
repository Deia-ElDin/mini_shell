/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:28:40 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/28 18:20:10 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	ast_add(t_data *data, t_ast *head, char direction)
{
	if (!head)
		return ;
	if (direction == 'l')
	{
		head->left = ast_head(data, head, 'l');
		if (!head->left || data->highest_token == 0)
			return ;
		ast_add(data, head->left, 'l');
		ast_add(data, head->left, 'r');
	}
	else
	{
		head->right = ast_head(data, head, 'r');
		if (!head->right || data->highest_token == 0)
			return ;
		ast_add(data, head->right, 'l');
		ast_add(data, head->right, 'r');
	}
}
