/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:14:17 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/25 16:16:56 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_path(t_data *data, char *cmd, char *var)
{
	char	**paths_split;
	char	*path;
	int		i;

	i = -1;
	if (!env_get(data, var) || !env_get(data, var)->value)
		return (NULL);
	paths_split = ft_split(env_get(data, var)->value, ':');
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
	ft_free(&paths_split, 'a');
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_data *data)
{
	char	*path;

	path = NULL;
	if (!cmd)
		return (NULL);
	else if (cmd && !ft_strncmp(cmd, "./", 2))
		path = ft_strdup(cmd);
	else if (cmd && !ft_strncmp(cmd, "/", 1))
		path = ft_strdup(cmd);
	else
		path = get_path(data, cmd, "PATH");
	return (path);
}
