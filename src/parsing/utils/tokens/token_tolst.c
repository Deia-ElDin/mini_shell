/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tolst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:28:31 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 18:59:50 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * The purpose of this function is to create the tokens (recursively)
 * we loop over the line till we find a special char
 * if we find a special char we create an add the token to the linked list
 * then we check the different cases i.e (>>, <<, >, <, |, " ", ' ')
 * if we find any of them we create and add the token to the linked list
 * unless if it was a quote we loop over the line till we find the closing quote
 * then we create and add the token to the linked list
 
 * token_add(data, head, start, i - start); 
 * => because we have reached a char (" |><\"\'") that we don't want to include
 * token_add(data, head, i++, 2); 
 * => because we have a double redirect
 * token_add(data, head, i, 1); 
 * => because we have a single special char
 * token_add(data, head, start, i - start + 1); 
 * => because we have a reached a quote that we want to include
 * token_tolst(data, head, i + 1);
 * => we call the function recursively to continue the loop with the next i
*/

void	token_tolst(t_data *data, t_token **head, unsigned int start)
{
	unsigned int	i;

	i = start;
	while (data->line[i] && !ft_strchr(" |><\"\'", data->line[i]))
		i++;
	token_add(data, head, start, i - start);
	if (!data->line[i])
		return ;
	if (ft_isdouble_redirect(&(data->line[i])))
		token_add(data, head, i++, 2);
	else if (ft_strchr(" |><", data->line[i]))
		token_add(data, head, i, 1);
	else if (ft_isquote(data->line[i]))
	{
		start = i;
		while (data->line[++i] && data->line[i] != data->line[start])
			;
		token_add(data, head, start, i - start + 1);
	}
	token_tolst(data, head, i + 1);
}
