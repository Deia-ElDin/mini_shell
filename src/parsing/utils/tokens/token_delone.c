/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_delone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:02:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/17 17:29:13 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_delone(t_token **node);

/// @brief Used to delete a token node
/// @param node The node to delete
void	token_delone(t_token **node)
{
	if (!node)
		return ;
	free((*node)->value);
	(*node)->value = NULL;
	free(*node);
	*node = NULL;
}
