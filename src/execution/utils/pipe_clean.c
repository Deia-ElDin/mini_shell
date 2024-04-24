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

int	reset_fds(t_data *data)
{
	// if (close (data->pipe[0]))
	// 	return (ft_putstr_fd("resetting FDs FAILED close of pipe 0\n", 2), 1);
	// if (close (data->pipe[1]))
	// 	return (ft_putstr_fd("resetting FDs FAILED close of pipe 1\n", 2), 1);
	// if (dup2(data->saved_stdfds[0], 0) == -1)
	// 	return (ft_putstr_fd("resetting FDs FAILED dup2 of 0\n", 2), 1);
	if (dup2(data->saved_stdfds[1], 1) == -1)
		return (ft_putstr_fd("resetting FDs FAILED dup2 of 1\n", 2), 1);
	// if (close (data->pipe[0])) || close (data->pipe[1])
	// 	|| dup2(data->saved_stdfds[0], 0) == -1
	// 	|| dup2(data->saved_stdfds[1], 1) == -1)
	// 	return (ft_putstr_fd("reset FDs FAILED\n", 2), 1);
	return (ft_putstr_fd("resetting FDs\n", 2), 0);
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
