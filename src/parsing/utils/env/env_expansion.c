/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:11:02 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 19:53:49 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

// "1234 $PATH1  567"
// "1234 $PATH  567"
// "1234 $PATH 567"
// "1234 $PATH 567"
// "$PATH 4567"
// "$PATH"
// '$PATH'

char	*ret_expansion(t_data *data, char *key, char *start, char *end)
{
	t_env	*node;
	char	*ret;

	ret = NULL;
	node = env_get(data, key);
	ft_free(&key, 'p');
	if (!node)
		ret = ft_strjoin(start, end);
	else
		ret = ft_strjoin_multi(3, start, node->value, end);
	if (!ret)
		exit_failure(data);
	return (ret);
}

char	*env_expansion(t_data *data, char *str)
{
	char	*key;
	int		i;
	int		dlr_start;
	int		dlr_end;

	if (!str || !*str || !ft_strchr(str, '$'))
		return (NULL);
	i = 0;
	dlr_start = 0;
	dlr_end = 0;
	while (str[i] && str[i] != '$')
		i++;
	dlr_start = i + 1;
	while (str[i] && !ft_isspace(str[i]) && !ft_isquote(str[i]))
		i++;
	dlr_end = i;
	key = ft_strndup(str + dlr_start, dlr_end - dlr_start);
	if (!key)
		exit_failure(data);
	str[dlr_start - 1] = '\0';
	return (ret_expansion(data, key, str, str + dlr_end));
}
