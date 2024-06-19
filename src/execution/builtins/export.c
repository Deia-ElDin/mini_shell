/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 16:01:20 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/19 15:14:40 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**sort_arr(char **arr);
static void	print_arr(char **arr);
static void	args_cases(t_data *data, char *args);
static void	export_err(t_data *data, char *err);
void		export(t_data *data);

static char	**sort_arr(char **arr)
{
	int		i;
	int		sorted;
	char	*tmp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = 0;
		while (arr[i] && arr[i + 1])
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				sorted = 0;
			}
			i++;
		}
	}
	return (arr);
}

static void	print_arr(char **arr)
{
	char	*equal_sign;
	char	*value;
	int		i;

	i = 0;
	while (arr[i])
	{
		equal_sign = ft_strchr(arr[i], '=');
		ft_putstr_fd("declare -x ", 1);
		if (equal_sign)
		{
			*equal_sign = '\0';
			value = equal_sign + 1;
			ft_putstr_fd(arr[i], 1);
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(value, 1);
			ft_putendl_fd("\"", 1);
			*equal_sign = '=';
		}
		else
			ft_putendl_fd(arr[i], 1);
		i++;
	}
}

static	void	args_cases(t_data *data, char *args)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (ft_strnstr(args, "+=", ft_strlen(args)))
	{
		key = ft_strndup(args, ft_strchr(args, '+') - args);
		value = ft_strdup(ft_strchr(args, '=') + 1);
		if (!key || !value)
			return (data_status(data, 1));
		env_concat(data, key, value);
	}
	else if (ft_strchr(args, '='))
	{
		key = ft_strndup(args, ft_strchr(args, '=') - args);
		value = ft_strdup(ft_strchr(args, '=') + 1);
		if (!key || !value)
			return (data_status(data, 1));
		env_set(data, key, value, true);
	}
	else
		env_set(data, args, "", false);
	ft_free(&key, 'p');
	ft_free(&value, 'p');
}

static void	export_err(t_data *data, char *err)
{
	ft_putstr_fd(ERR_PROMPT, STDERR_FILENO);
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	data_status(data, 1);
}

/// @brief The export builtin command
/// @param data The main struct
void	export(t_data *data)
{
	t_env	*oldpwd_env;
	char	**sorted_env;
	char	**cmds;

	cmds = data->ast->right->cmd;
	oldpwd_env = env_get(data, "OLDPWD");
	if (!oldpwd_env)
		env_set(data, "OLDPWD", "", false);
	if (cmds[1] && !ft_isalpha(*cmds[1]) && *cmds[1] != '_')
		return (export_err(data, cmds[1]));
	if (cmds[1])
	{
		if (ft_strchr(cmds[1], '=') && !ft_isalpha(*cmds[1]))
			return (export_err(data, cmds[1]));
		if (!ft_isalpha(*cmds[1]) && *cmds[1] != '_')
			return (export_err(data, cmds[1]));
		if (ft_strchr(cmds[1], '-'))
			return (export_err(data, cmds[1]));
		return (args_cases(data, cmds[1]));
	}
	sorted_env = sort_arr(data->env_arr);
	print_arr(sorted_env);
	data->exit_status = 0;
}
