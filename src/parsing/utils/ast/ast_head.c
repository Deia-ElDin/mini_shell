/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_head.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:21:18 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/28 12:08:15 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_ast	*ast_head(t_data *data, t_ast *head, char direction)
{
	if (head)
		data->highest_token = head->token->type;
	else
		data->highest_token = TOKEN_AND;
	if (direction == 'l')
		return (ast_left(data, head));
	else if (direction == 'r')
		return (ast_right(data, head));
	return (NULL);
}
