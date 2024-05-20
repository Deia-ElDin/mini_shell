/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:15:37 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/20 16:40:51 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_cmd(t_ast *ast, t_data *data)
{
	data->ast = ast->left;
	if (ast->left->left && ast->left->right)
		execution(data);
	data->ast = ast->right;
	if (ast->right->left && ast->right->right)
		execution(data);
	return (0);
}
