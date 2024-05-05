/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:41:55 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/29 13:41:58 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_redirs(t_ast *ast, t_data *data)
{
	if (ast->type == NODE_REDIR_OUT)
	{	
		if (!redirect_out(ast, data))
			return (0);
	}
	else if (ast->type == NODE_REDIR_IN)
	{	
		if (!redirect_in(ast, data))
			return (0);
	}
	else if (ast->type == NODE_HEREDOC && !here_doc(ast, data))
		return (0);
	else if (ast->type == NODE_APPEND && !append(ast, data))
		return (0);
	else if (ast->type == NODE_WORD)
		return (0);
	return (1);
}

int	redirect_in(t_ast *ast, t_data *data)
{
	data->file_fd = open(ast->file, O_RDONLY, 0777);
	if (data->file_fd == -1)
		return (1);
	data->redirect_flag = -1;
	dup2(data->file_fd, 0);
	return (0);
}

int	redirect_out(t_ast *ast, t_data *data)
{
	unlink(ast->file);
	data->file_fd = open(ast->file, O_CREAT | O_WRONLY, 0777);
	if (data->file_fd == -1)
		return (1);
	data->redirect_flag = 1;
	dup2(data->file_fd, 1);
	return (0);
}

int	here_doc(t_ast *ast, t_data *data)
{
	int	status;

	(void)ast;
	status = 0;
	data->redirect_flag = -2;
	return (status);
}

int	append(t_ast *ast, t_data *data)
{

	data->file_fd = open(ast->file, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (data->file_fd == -1)
		return (1);
	data->redirect_flag = 2;
	dup2(data->file_fd, 1);
	return (0);
}
