/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/21 17:29:56 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_for_sleep(int pid, char *cmd, int last)
{
	int	status;

	status = 0;
	if (ft_strnstr(cmd, "sleep", ft_strlen(cmd))
		|| last)
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
