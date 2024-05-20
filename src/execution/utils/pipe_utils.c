/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/20 13:55:21 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pipe_for_next(t_data *data, t_ast *ast_right)
{
	if (data->redirect_flag != 0)
		data->redirect_flag = 0;
	if (ast_right->head->head && ast_right->head->head->type == NODE_PIPE)
	{
		close(ast_right->head->head->pipe[1]);
		if (!ast_right->end_flag)
		{
			dup2(ast_right->head->head->pipe[0], 0);
			close(ast_right->head->head->pipe[0]);
		}
		else
			close(ast_right->head->head->pipe[0]);
	}
}

int	check_for_sleep(int pid, char *cmd, int last)
{
	int	status;

	status = 0;
	if (ft_strnstr(cmd, "sleep", ft_strlen(cmd))
		|| !last)
		waitpid(pid, &status, 0);
	else
		waitpid(pid, &status, 0);
	return (status);
}

char	*gnl_till_null(int *pipe_fd, char *str)
{
	char	*temp;

	temp = ft_get_next_line(pipe_fd[1]).line;
	while (temp)
	{
		str = join_strs(str, temp);
		free(temp);
		temp = ft_get_next_line(pipe_fd[1]).line;
	}
	return (str);
}
