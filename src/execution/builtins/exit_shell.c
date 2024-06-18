/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:01:22 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/18 21:03:49 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *data)
{
	t_atoi	res;
	int		exit_code;

	if (data->ast->right->cmd[2])
		data->exit_status = 1;
	else if (ft_isalpha(data->ast->right->cmd[1][0]))
		data->exit_status = 2;
	else if (data->ast->right->cmd[1])
	{
		res = ft_atoi(data->ast->right->cmd[1]);
		if (res.error)
			exit_code = 255;
		data->exit_status = res.nbr;
	}
	if (data->exit_status < 0)
		data->exit_status = 256 + (data->exit_status % 256);
	else if (data->exit_status > 255)
		data->exit_status %= 256;
	exit_code = data->exit_status;
	data_free(data);
	exit(exit_code);
}
