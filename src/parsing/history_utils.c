/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:54:44 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/13 14:26:11 by dehamad          ###   ########.fr       */
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


// t_history	*add_history(char *line, t_history *new_history)
// {
	
// }




























// t_history	*add_history(char *line, t_history *history)
// {
// 	t_history	*new;

// 	if (!line || !*line)
// 		return (history);
// 	new = (t_history *)ft_calloc(1, sizeof(t_history));
// 	if (!new)
// 		exit(1);
// 	new->line = ft_strdup(line);
// 	if (!new->line)
// 		exit(1);
// 	if (!history->head)
// 	{
// 		history->head = new;
// 		history->current = new;
// 	}
// 	else
// 	{
// 		history->current->next = new;
// 		new->prev = history->current;
// 		history->current = new;
// 	}
// 	return (history);
// }

