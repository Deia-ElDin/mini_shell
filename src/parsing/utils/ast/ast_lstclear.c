/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:24:06 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/06 17:01:19 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	recursive_free(t_ast **lst)
{
	if (*lst)
	{
		recursive_free(&(*lst)->left);
		recursive_free(&(*lst)->right);
		ft_free(&(*lst)->cmd, 'a');
		free(*lst);
		*lst = NULL;
	}
}

void	ast_lstclear(t_data *data)
{
	recursive_free(&data->ast);
	data->ast = NULL;
}
