/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:11:02 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 20:26:35 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * The purpose of this function is to return the expansion
 * start = the string before the $ sign (which we null terminated)
 * end = the string after the expansion (which is str + exp_end)
 * we get the node by calling env_get
 * we free the key since we don't need it any more
 * if the node is NULL we return the concatenation of start and end
 * else we return the concatenation of start, node->value and end
 * if we fail to allocate memory at any time 
 * we exit the program with exit_failure which frees all the located memories
*/

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

/**
 * The purpose of this function is to expand the environment variable
 * if (!str || !*str || !ft_strchr(str, '$')) 
 * => if str = null || *str = "\0" || !ft_strchr(str, '$') we return NULL
 * exp_start = expansion (the dollar sign + the key) starting index
 * exp_end = expansion ending index
 * we loop over the string until we find a $ character => exp_start = i + 1
 * exp_start = i + 1 cuz we want to start from the next character after the $
 * we loop over the string until we find a space or a quote => exp_end = i
 * we get the key by copying the string at exp_start and n = exp_end - exp_start
 * we set the character at exp_start - 1 to '\0' to remove the $ character
 * exp_start - 1 cuz we already went 1 step ahead to get the key
 * now our str right before the $ character is null terminated
*/

char	*env_expansion(t_data *data, char *str)
{
	char	*key;
	int		i;
	int		exp_start;
	int		exp_end;

	if (!str || !*str || !ft_strchr(str, '$'))
		return (NULL);
	i = 0;
	exp_start = 0;
	exp_end = 0;
	while (str[i] && str[i] != '$')
		i++;
	exp_start = i + 1;
	while (str[i] && !ft_isspace(str[i]) && !ft_isquote(str[i]))
		i++;
	exp_end = i;
	key = ft_strndup(str + exp_start, exp_end - exp_start);
	if (!key)
		exit_failure(data);
	str[exp_start - 1] = '\0';
	return (ret_expansion(data, key, str, str + exp_end));
}
