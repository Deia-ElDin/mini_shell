/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:15:37 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/21 18:08:03 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_cmd(t_data *data)
{
	t_ast	*ast;
	t_ast	*left;

	ast = data->ast;
	left = ast->left;
	if (left->type <= NODE_CMD)
	{
		prepare_pipe(left);
		left->thereispipe = true;
		ast->right->thereisprev = true;
		ast->right->prev_pipe = left->pipe;
	}
	if (left->type == NODE_PIPE)
	{
		left = left->right;
		prepare_pipe(left);
		left->thereispipe = true;
		ast->right->thereisprev = true;
		ast->right->prev_pipe = left->pipe;
	}
	return (0);
}
