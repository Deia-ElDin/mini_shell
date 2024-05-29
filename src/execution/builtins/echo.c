/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:01:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/21 13:01:15 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (data->ast->right->cmd[i]
		&& ft_strcmp(data->ast->right->cmd[i], "-n") == 0)
	{
		n_flag = true;
		i++;
	}
	while (data->ast->right->cmd[i])
	{
		ft_putstr_fd(data->ast->right->cmd[i], STDOUT_FILENO);
		if (data->ast->right->cmd[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
