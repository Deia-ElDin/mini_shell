/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:55 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/10 14:32:55 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(t_ast *ast, t_ast *head)
{
	ft_putstr_fd("inside of redirect_in\n", 2);
	ast->redir_in->fd = open(ast->redir_in->file, O_RDONLY, 0755);
	if (ast->redir_in->fd == -1)
		return (0);
	head->in_fd = &(ast->redir_in->fd);
	return (1);
}

int	redirect_out(t_ast *ast, t_ast *head)
{
	ft_putstr_fd("inside of redirect_out\n", 2);
	ast->redir_out->fd = open(ast->redir_out->file, O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (ast->redir_out->fd == -1)
		return (0);
	head->out_fd = &(ast->redir_out->fd);
	return (1);
}

int	append(t_ast *ast, t_ast *head)
{
	ft_putstr_fd("inside of append\n", 2);
	ast->redir_append->fd = open(ast->redir_append->file, O_CREAT | O_WRONLY | O_APPEND, 0755);
	if (ast->redir_append->fd == -1)
		return (0);
	head->out_fd = &(ast->redir_append->fd);
	return (1);
}

int	check_for_redirs(t_ast *ast)
{
	t_ast	*head;

	head = ast;
	while (head && head->head && head->type != NODE_CMD)
		head = head->head;
	while (ast)
	{
		if (ast->type == NODE_REDIR && ast->redir_out->exists)
		{
			if (!redirect_out(ast, head))
				return (0);
		}
		else if (ast->type == NODE_REDIR && ast->redir_in->exists)
		{
			if (!redirect_in(ast, head))
				return (0);
		}
		else if (ast->type == NODE_REDIR && ast->redir_append->exists && !append(ast, head))
			return (0);
		else if (ast->type == NODE_WORD)
			return (1);
		ast = ast->right;
	}
	return (1);
}
