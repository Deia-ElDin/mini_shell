/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_lstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 08:24:06 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/26 14:08:41 by melshafi         ###   ########.fr       */
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
		if ((*lst)->heredoc && (*lst)->heredoc->exists)
		{
			unlink((*lst)->heredoc->file);
			free((*lst)->heredoc->file);
		}
		if ((*lst)->heredoc)
			free((*lst)->heredoc);
		if ((*lst)->redir_in)
			free((*lst)->redir_in);
		if ((*lst)->redir_out)
			free((*lst)->redir_out);
		if ((*lst)->redir_append)
			free((*lst)->redir_append);
		free(*lst);
		*lst = NULL;
	}
}

void	ast_lstclear(t_data *data)
{
	recursive_free(&data->ast);
	data->ast = NULL;
}
