/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:54:44 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/11 18:13:57 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_history	*init_history(t_history *history)
{
	history = (t_history *)ft_calloc(1, sizeof(t_history));
	if (!history)
		exit(1);
	history->line = NULL;
	history->next = NULL;
	history->prev = NULL;
	history->head = NULL;
	history->current = NULL;
	return (history);
}


