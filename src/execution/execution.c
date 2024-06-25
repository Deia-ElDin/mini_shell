/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:26:03 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/12 12:26:04 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *data)
{
	t_ast	*ast;

	ast = data->ast;
	if (!data || !ast)
		return ;
	if (data->ast->type == NODE_PIPE)
		pipe_cmd(data);
	data->ast = ast->left;
	if (data->ast->type >= NODE_CMD)
		execution(data);
	data->ast = ast->right;
	if (data->ast->type >= NODE_CMD)
		execution(data);
	data->ast = ast;
	if (ast->type == NODE_CMD)
		simple_cmd(data);
}

void	wait_on_pids(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->curr_pid)
	{
		if (!data->pids[i].ast)
			data->exit_status = 1;
		else
			data->exit_status = check_for_sleep(data->pids[i].pid, data->pids[i].ast, data->pids[i].ast->right->end_flag);
		i++;
	}
	free(data->pids);
}
