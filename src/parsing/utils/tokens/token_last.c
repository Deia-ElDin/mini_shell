/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:12:45 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/27 08:12:58 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

t_token	*token_last(t_data *data)
{
	t_token	*token;

	if (!data->tokens)
		return (NULL);
	token = data->tokens;
	while (token->next)
		token = token->next;
	return (token);
}
