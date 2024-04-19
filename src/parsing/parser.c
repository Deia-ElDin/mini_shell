/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:27:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/19 22:23:25 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*parser(t_data *data)
{
	t_ast	*head;
	t_token	*tokens;
	t_ast	*new_node;

	head = NULL;
	tokens = data->tokens;
	while (tokens)
	{
		new_node = new_ast(tokens->type);
		add_ast(&head, new_node);
		tokens = tokens->next;
	}
	return (head);
}
