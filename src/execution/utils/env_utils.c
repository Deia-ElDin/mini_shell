/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:14:17 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/24 14:01:20 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*get_cmd_path(char *cmd, t_data *data)
{
	char	*path;

	path = NULL;
	if (cmd && !access(cmd, F_OK | X_OK))
			path = ft_strdup(cmd);
	else if (cmd && !ft_strncmp(cmd, "./", 2))
		path = get_path(data->env, &cmd[2], "PWD");
	else
		path = get_path(data->env, cmd, "PATH");
	return (path);
}

char	*get_all_paths(char **envp, char *var)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		path = ft_substr(envp[i], 0, j);
		if (ft_strcmp(path, var) == 0)
		{
			free(path);
			return (&envp[i][j + 1]);
		}
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path(char **envp, char *cmd, char *var)
{
	char	**paths_split;
	char	*path;
	int		i;

	i = -1;
	paths_split = ft_split(get_all_paths(envp, var), ':');
	if (!paths_split)
		return (NULL);
	while (paths_split[++i])
	{
		path = join_strs(ft_strjoin(paths_split[i], "/"), cmd);
		if (path && !access(path, F_OK | X_OK))
		{
			free_2dchar(paths_split);
			return (path);
		}
		free(path);
	}
	free_2dchar(paths_split);
	return (NULL);
}
