/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:15:37 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/20 12:19:28 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_cmd(t_ast *ast, t_data *data)
{
	if (data->pipe[0] == -1 && data->pipe[1] == -1)
	{
		if (pipe(data->pipe) == -1)
			return (ft_putstr_fd("ERR\n", 2), 1);
	}
	if (ast->left->left && ast->left->right)
		exec_ast(ast->left, data);
	if (ast->right->left && ast->right->right)
		exec_ast(ast->right, data);
	return (0);
}
