/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:27:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/14 15:43:57 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parser(t_data *data)
{
	t_ast	*ast;
	t_token	*tokens;
	t_ast	*new_node;
	// char	*line;

	ast = NULL;
	// line = data->line;
	tokens = data->tokens;
	while (tokens)
	{
		new_node = new_ast(tokens->type);
		add_ast(&ast, new_node);
		tokens = tokens->next;
	}
	return (ast);
}
