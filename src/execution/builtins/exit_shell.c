/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:01:22 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/26 14:34:29 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_include_letters(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (ft_isalpha(cmd[i]))
			return (print_error(cmd, "numeric argument required"), true);
	return (false);
}

void	exit_shell(t_data *data)
{
	t_atoi	res;
	int		exit_code;

	if (data->ast->right->cmd[1] && data->ast->right->cmd[2])
	{
		data->exit_status = 1;
		return (print_error("exit", "too many arguments"));
	}
	else if (data->ast->right->cmd[1]
		&& is_include_letters(data->ast->right->cmd[1]))
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
