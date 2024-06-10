/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:22 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/05 15:44:02 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_file_name(t_ast *ast, char *file)
{
	int			i;

	i = 0;
	while (ast->head && ast->type != NODE_CMD)
		ast = ast->head;
	if (ast->type == NODE_CMD)
	{
		while (ast->right->cmd[i])
			file = ft_strjoin(file, ast->right->cmd[i++]);
		file = ft_strjoin(file, ft_itoa(ast->right->token->index));
	}
	return (file);
}

static void	set_prev_exists(t_ast *ast)
{
	while (ast->head && ast->type != NODE_CMD)
		ast = ast->head;
	if (ast->type == NODE_CMD)
		ast->prev_exists = true;
}

static void	read_heredoc(char *file, t_ast *ast)
{
	char	*str;

	str = readline("> ");
	ast->heredoc->file = file;
	while (ft_strcmp(str, ast->heredoc->stop_key))
	{
		ft_putstr_fd(str, ast->heredoc->fd);
		ft_putstr_fd("\n", ast->heredoc->fd);
		str = readline("> ");
	}
	close (ast->heredoc->fd);
	ast->heredoc->fd = open(file, O_RDONLY, 0755);
	if (ast->heredoc->fd == -1)
		perror("open failed");
}

static int	check_for_heredoc(t_ast *ast, t_data *data)
{
	t_env		*tmp;
	char		*file;

	ft_putstr_fd("		CHECKING HEREDOC\n", 2);
	if (!ast->heredoc->exists)
		return (0);
	ft_putstr_fd("		INSIDE HEREDOC\n", 2);
	set_prev_exists(ast);
	tmp = env_get(data, "TMPDIR");
	if (!tmp)
	{
		file = env_get(data, "PWD")->value;
		file = ft_strjoin(file, "/");
	}
	else
		file = tmp->value;
	file = set_file_name(ast, file);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
	ast->heredoc->fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0775);
	if (ast->heredoc->fd == -1)
		return (perror("open failed"), ft_putstr_fd("\n", 2), 0);
	return (read_heredoc(file, ast), 1);
}

void	prepare_heredocs(t_ast *ast, t_data *data)
{
	ft_putstr_fd("		LOOPING HEREDOC\n", 2);
	if (!ast || !data)
		return ;
	if (ast->type == NODE_REDIR)
		check_for_heredoc(ast, data);
	prepare_heredocs(ast->left, data);
	prepare_heredocs(ast->right, data);
}
