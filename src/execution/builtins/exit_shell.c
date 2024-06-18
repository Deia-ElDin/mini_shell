/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:01:22 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/18 20:37:15 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *data)
{
	t_atoi	res;
	int		exit_code;

	if (data->ast->right->cmd[1])
	{
		res = ft_atoi(data->ast->right->cmd[1]);
		if (res.error)
			exit_code = 255;
		data->exit_status = res.nbr;
	}
	exit_code = data->exit_status;
	data_free(data);
	exit(exit_code);
}
