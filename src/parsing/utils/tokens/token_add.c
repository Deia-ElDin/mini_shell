/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 02:46:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 11:58:16 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * The purpose of this function is to add a token to the linked list
 * we create a new token
 * we loop over the linked list to get the last token
 * if the head is NULL we set the head to the token
 * else we set the last token next to the new token
*/

void	token_add(t_data *data, t_token **head, int start, int len)
{
	t_token	*token;
	t_token	*tmp;

	token = token_new(data, start, len);
	if (!token)
		return ;
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!*head)
		*head = token;
	else
	{
		tmp->next = token;
		token->prev = tmp;
	}
}
