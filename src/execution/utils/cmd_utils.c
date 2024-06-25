/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:32:54 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/25 18:58:43 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	prep_command_execution(pid_t pid, t_data *data, t_ast *ast, char *path)
{
	pid = fork();
	if (pid < 0)
		ft_putstr_fd("fork failed\n", 2);
	if (pid < 0)
		data->exit_status = pid;
	if (pid == 0)
		call_child(path, ast->right, data);
	else if (pid > 0)
		call_parent(pid, ast, data);
}

int	check_for_sleep(int pid, t_ast *ast, int last)
{
	int		status;
	char	*cmd;

	cmd = ast->left->cmd[0];
	status = 0;
	if (ft_strnstr(cmd, "sleep", ft_strlen(cmd))
		|| last)
		waitpid(pid, &status, 0);
	else
		waitpid(pid, &status, WCONTINUED);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	else
		return (status);
}
