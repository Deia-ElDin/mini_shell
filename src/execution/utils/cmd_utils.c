/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/19 13:01:36 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_sleep(int pid, char *cmd, int last)
{
	int	status;

	status = 0;
	if (ft_strnstr(cmd, "sleep", ft_strlen(cmd))
		|| last)
		waitpid(pid, &status, 0);
	else
		waitpid(pid, &status, WNOHANG);
	// ft_putstr_fd("2Testing exit code: ", 2);
	// ft_putnbr_fd(status, 2);
	// ft_putstr_fd("\n", 2);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (status);
}
