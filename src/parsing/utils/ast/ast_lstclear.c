/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:24:06 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/28 13:29:52 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	recursive_free(t_ast **lst)
{
	if (*lst)
	{
		if ((*lst)->left)
			recursive_free(&(*lst)->left);
		if ((*lst)->right)
			recursive_free(&(*lst)->right);
		ft_free(&(*lst)->cmd, 'a');
		if ((*lst)->type == NODE_PIPE)
		{
			close((*lst)->pipe[0]);
			close((*lst)->pipe[1]);
		}
		free(*lst);
		*lst = NULL;
	}
}

void	ast_lstclear(t_data *data)
{
	recursive_free(&data->ast);
	data->ast = NULL;
}
