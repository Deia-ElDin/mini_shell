/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/24 17:00:59 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pipe_for_next(t_data *data, int	end_flag)
{
	if (data->pipe[0] >= 0 || data->pipe[1] >= 0)
	{
		close(data->pipe[1]);
		dup2(data->pipe[0], 0);
	}
}

int	check_for_sleep(int pid, char *cmd, t_ast *ast_left, t_ast *ast_right)
{
	int status;

	status = 0;
	if (ft_strnstr(cmd, "sleep", ft_strlen(cmd))
		|| !ast_left->end_flag || !ast_right->end_flag)
		waitpid(pid, &status, 0);
	else
		waitpid(pid, &status, WNOHANG);
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
