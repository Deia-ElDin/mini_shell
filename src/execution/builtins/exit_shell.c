/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:01:22 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/19 12:53:11 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *data)
{
	t_atoi	res;
	int		exit_code;

	if (data->ast->right->cmd[2])
		data->exit_status = 1;
	else if (data->ast->right->cmd[1] && ft_isalpha(data->ast->right->cmd[1][0]))
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
