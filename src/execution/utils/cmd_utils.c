/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/18 15:55:46 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_sleep(t_data *data, int pid, char *cmd, int last)
{
	int	status;

	if (data->exit_status)
		return (data->exit_status);
	status = 0;
	if (ft_strnstr(cmd, "sleep", ft_strlen(cmd))
		|| last)
		waitpid(pid, &status, 0);
	else
		waitpid(pid, &status, WNOHANG);
	return (status);
}
