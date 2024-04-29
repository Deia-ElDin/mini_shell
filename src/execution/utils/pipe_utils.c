/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/29 15:48:46 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pipe_for_next(t_data *data, int last)
{
	if (data->redirect_flag != 0)
		data->redirect_flag = 0;
	if (data->pipe[0] >= 0 || data->pipe[1] >= 0)
	{
		close(data->pipe[1]);
		if (last)
		{
			dup2(data->pipe[0], 0);
			close(data->pipe[0]);
		}
		else
			close(data->pipe[0]);
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
