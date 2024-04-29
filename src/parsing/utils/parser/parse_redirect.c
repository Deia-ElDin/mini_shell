/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:34:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/28 19:48:30 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	parse_redirect(t_data *data, t_token *token)
{
	t_ast	*new_node;

	new_node = ast_new(data, token);
	if (!new_node)
		exit_failure(data);
	data->ast = data->ast;
	if (!data->ast)
		data->ast = new_node;
	else
	{
		new_node->left = data->ast;
		data->ast = new_node;
	}
}
