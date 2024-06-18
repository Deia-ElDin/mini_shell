/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:37:28 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/18 20:07:49 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_error(t_data *data, char *msg, bool full_msg);
static char	*get_path(t_data *data);
void		cd(t_data *data);

static void	cd_error(t_data *data, char *msg, bool full_msg)
{
	int	fd;

	fd = STDERR_FILENO;
	ft_putstr_fd("bash: cd: ", fd);
	ft_putstr_fd(msg, fd);
	if (full_msg && errno)
	{
		ft_putstr_fd(": ", fd);
		ft_putstr_fd(strerror(errno), fd);
	}
	ft_putchar_fd('\n', fd);
	data->exit_status = 1;
}

static char	*get_path(t_data *data)
{
	t_env	*env_var;
	char	*path;

	path = data->ast->right->cmd[1];
	if (!path || !ft_strcmp(path, "~"))
	{
		env_var = env_get(data, "HOME");
		if (!env_var || !env_var->value)
			return (cd_error(data, "HOME not set", true), NULL);
		path = env_var->value;
	}
	else if (!ft_strcmp(path, "-"))
	{
		env_var = env_get(data, "OLDPWD");
		if (!env_var || !env_var->value)
			return (cd_error(data, "OLDPWD not set", true), NULL);
		path = env_var->value;
	}
	path = ft_strdup(path);
	if (!path)
		return (data->exit_status = 1, NULL);
	return (path);
}

/// @brief Used to change the current working directory
/// @param data The main struct
void	cd(t_data *data)
{
	char	*path;
	char	cwd[1024];

	if (data->ast->right->cmd[2])
		return (cd_error(data, "too many arguments", false));
	path = get_path(data);
	if (!path)
		return ;
	if (!getcwd(cwd, sizeof(cwd)))
		return (cd_error(data, "getcwd failed", true));
	env_set(data, "OLDPWD", cwd, true);
	if (chdir(path) != 0)
		return (cd_error(data, path, true), free(path));
	free(path);
	if (!getcwd(cwd, sizeof(cwd)))
		return (cd_error(data, "getcwd failed", true));
	env_set(data, "PWD", cwd, true);
	data->exit_status = 0;
}
