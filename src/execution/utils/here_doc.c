/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:22 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/05 11:21:12 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(char *file, t_ast *ast)
{
	char	*str;

	str = readline("> ");
	ast->right->heredoc->file = file;
	while (ft_strcmp(str, ast->right->heredoc->stop_key))
	{
		ft_putstr_fd(str, ast->right->heredoc->fd);
		ft_putstr_fd("\n", ast->right->heredoc->fd);
		str = readline("> ");
	}
	close (ast->right->heredoc->fd);
	ast->right->heredoc->fd = open(file, O_RDONLY, 0755);
	if (ast->right->heredoc->fd == -1)
		perror("open failed");
}

static int	check_for_heredoc(t_ast *ast, t_data *data)
{
	t_env		*tmp;
	char		*file;
	int			i;

	if (!ast->right->heredoc->exists)
		return (0);
	i = 0;
	ast->prev_exists = true;
	tmp = env_get(data, "TMPDIR");
	if (!tmp)
	{
		file = env_get(data, "PWD")->value;
		file = ft_strjoin(file, "/");
	}
	else
		file = tmp->value;
	while (ast->right->cmd[i])
		file = ft_strjoin(file, ast->right->cmd[i++]);
	file = ft_strjoin(file, ft_itoa(ast->right->token->index));
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
	ast->right->heredoc->fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0775);
	if (ast->right->heredoc->fd == -1)
		return (perror("open failed"), ft_putstr_fd("\n", 2), 0);
	return (read_heredoc(file, ast), 1);
}

void	prepare_heredocs(t_ast *ast, t_data *data)
{
	if (!ast || !data)
		return ;
	if (ast->type == NODE_CMD && ast->right->type == NODE_REDIR)
		check_for_heredoc(ast, data);
	if (ast->left && ast->left->type >= NODE_CMD)
		prepare_heredocs(ast->left, data);
	if (ast->right && ast->right->type >= NODE_CMD)
		prepare_heredocs(ast->right, data);
}
