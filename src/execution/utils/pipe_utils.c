/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:54:07 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/21 17:01:24 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_first_pipe(t_ast *ast)
{
	if (ast->left && ast->left->type == NODE_PIPE)
		return (0);
	else
		return (1);
}

int	is_last_pipe(t_ast *ast)
{
	if (ast->head && ast->head->type == NODE_PIPE)
		return (0);
	else
		return (1);
}
