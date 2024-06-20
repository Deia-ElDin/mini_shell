/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tolst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:28:31 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/20 16:26:23 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_tolst(t_data *data, t_token **head, unsigned int start);

/// @brief Used to create the tokens (recursively) 
/// @param data The main struct
/// @param head The head of the token linked list
/// @param start The index of where we at the string
void	token_tolst(t_data *data, t_token **head, unsigned int start)
{
	unsigned int	i;

	i = start;
	while (data->line[i] && !ft_strchr(" |><\"\'", data->line[i]))
		i++;
	token_add(data, head, start, i - start);
	if (!data->line[i])
		return ;
	if (ft_isdoubles(&(data->line[i])))
		token_add(data, head, i++, 2);
	else if (ft_strchr(" |><", data->line[i]))
		token_add(data, head, i, 1);
	else if (ft_isquote(data->line[i]))
	{
		start = i;
		while (data->line[++i] && data->line[i] != data->line[start])
			;
		if (!data->line[i])
			return (data->error = true, syntax_error("quotes"));
		token_add(data, head, start, i - start + 1);
	}
	token_tolst(data, head, i + 1);
}

/**
 * The purpose of this function is to create the tokens (recursively)
 * we loop over the line till we encounter a special char (" |><\"\'") 
 * we create token with whatever we found so far till we found the special char
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
 * 
 * If (ft_isquote(data->line[i])) 
 * and we looped over the line and couldn't find the closing quote
 * we return and since everything thing inside the return is void
 * so basically we set an error and print it, 
 * then we exit this function only (and not the whole program)
 * then outside at the lexer function we clear the linked list
*/
