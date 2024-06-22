/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:01:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/19 15:14:15 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_data *data)
{
	int		i;
	bool	n_flag;
	char	*print_value;

	i = 1;
	n_flag = false;
	if (data->ast->right->cmd[i]
		&& ft_strcmp(data->ast->right->cmd[i], "-n") == 0)
	{
		n_flag = true;
		i++;
	}
	if (!data->ast->right->cmd[1])
		return ((void)ft_putchar_fd('\n', STDOUT_FILENO));
	print_value = data->ast->token->value;
	while (*print_value != ' ')
		print_value++;
	print_value++;
	ft_putstr_fd(print_value, STDOUT_FILENO);
	print_value = NULL;
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	data->exit_status = 0;
}
