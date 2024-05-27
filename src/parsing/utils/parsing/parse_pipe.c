/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:43:28 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/20 13:45:12 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	prepare_pipe(t_ast *new_node)
{
	if (pipe(new_node->pipe) == -1)
		ft_putstr_fd("ERR\n", 2);
}