/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:11:02 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 18:47:52 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// echo "1234 $PATH 456"
// echo "$PATH 4567"
// echo "$PATH"

// char	*get_extra_str(t_data *data, char *str, int *i)
// {
// 	char	*ret;
// 	int		index;

// 	ret = NULL;
// 	index = *i;
// 	while (str[*i] && str[*i] != '$')
// 		(*i)++;
// 	ret = ft_substr(str, index, *i - index);
// 	if (!ret)
// 		exit_failure(data);
// 	return (ret);
// }

// char	*get_expansion(t_data *data, char *str, int *i)
// {
// 	char	*ret;
// 	int		index;

// 	ret = NULL;
// 	index = *i;
// 	while (str[*i] && ft_isalnum(str[*i]))
// 		(*i)++;
// 	ret = ft_substr(str, index, *i - index);
// 	if (!ret)
// 		exit_failure(data);
// 	printf("ret = %s\n"	, ret);
// 	return (ret);
// }

// void	free_ptrs(char *start, char *expansion, char *end)
// {
// 	ft_free(&start, 'p');
// 	ft_free(&expansion, 'p');
// 	ft_free(&end, 'p');
// }

// char	*env_expansion(t_data *data, char *str)
// {
// 	char	*start;
// 	char	*expansion;
// 	char	*end;
// 	char	*ret;
// 	int		i;
// 	t_env	*node;

// 	if (!str || !*str || !ft_strchr(str, '$'))
// 		return (NULL);
// 	start = NULL;
// 	expansion = NULL;
// 	end = NULL;
// 	ret = NULL;
// 	i = 0;
// 	start = get_extra_str(data, str, &i);
// 	expansion = get_expansion(data, str, &i);
// 	end = get_extra_str(data, str, &i);
// 	node = env_get(data, expansion + 1);
// 	if (!node)
// 		ret = ft_strjoin(start, end);
// 	else
// 		ret = ft_strjoin_multi(3, start, node->value, end);
// 	free_ptrs(start, expansion, end);
// 	if (!ret)
// 		exit_failure(data);
// 	return (ret);
// }

char	*env_expansion(t_data *data, char *str)
{
	char	*start;
	char	*expansion;
	char	*end;
	char	*ret;
	int		index;
	int		i;
	t_env	*node;

	if (!str || !*str || !ft_strchr(str, '$'))
		return (NULL);
	start = NULL;
	expansion = NULL;
	end = NULL;
	ret = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] != '$')
		{
			index = i;
			while (str[i] && str[i] != '$')
				i++;
			start = ft_substr(str, index, i - index);
			if (!start)
				exit_failure(data);
		}
		if (str[i] && str[i] == '$')
		{
			index = i;
			while (str[i] && !ft_isspace(str[i]) && !ft_isquote(str[i]))
				i++;
			expansion = ft_substr(str, index, i - index);
			if (!expansion)
				exit_failure(data);
		}
		if (str[i] && str[i] != '$')
		{
			index = i;
			while (str[i] && str[i] != '$')
				i++;
			end = ft_substr(str, index, i - index);
			if (!end)
				exit_failure(data);
		}
	}
	node = env_get(data, expansion + 1);
	if (!node)
		ret = ft_strjoin(start, end);
	else
		ret = ft_strjoin_multi(3, start, node->value, end);
	ft_free(&start, 'p');
	ft_free(&expansion, 'p');
	ft_free(&end, 'p');
	if (!ret)
		exit_failure(data);
	printf("ret = %s\n", ret);
	return (ret);
}
