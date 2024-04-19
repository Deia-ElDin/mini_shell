/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:08:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/19 23:29:55 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * The purpose of this function is to create the tokens
*/

t_token	*lexer(t_data *data)
{
	t_token	*head;

	head = NULL;
	if (!(*data->line))
		return (NULL);
	create_tokens(data, &head, 0);
	return (head);
}
