/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:11:02 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/18 15:02:24 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_var_name(char **str)
{
	char	*start;

	if (**str == '?')
	{
		(*str)++;
		return (ft_strdup("?"));
	}
	start = *str;
	while (**str && !ft_isspace(**str) && !ft_isquote(**str))
		(*str)++;
	return (ft_strndup(start, *str - start));
}

static char	*expand_var(t_data *data, char *var_name)
{
	t_env	*node;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(data->exit_status));
	node = env_get(data, var_name);
	if (node)
		return (ft_strdup(node->value));
	return (ft_strdup(""));
}

static void	append_expanded_var(t_data *data, char **result, char **str)
{
	char	*var_name;
	char	*expanded;
	char	*new_result;

	var_name = extract_var_name(str);
	if (!*var_name)
		return ;
	expanded = expand_var(data, var_name);
	new_result = ft_strnjoin(2, *result, expanded);
	ft_free(result, 'p');
	*result = new_result;
	ft_free(&var_name, 'p');
	ft_free(&expanded, 'p');
}

static void	append_char(char **result, char c)
{
	char	*new_result;
	char	*ch;

	ch = ft_calloc(2, sizeof(char));
	if (!ch)
		return ;
	*ch = c;
	new_result = ft_strnjoin(2, *result, ch);
	ft_free(result, 'p');
	ft_free(&ch, 'p');
	*result = new_result;
}

char	*env_expansion(t_data *data, char *str)
{
	char	*result;

	result = ft_strdup("");
	while (*str)
	{
		if (*str == '$')
		{
			str++;
			append_expanded_var(data, &result, &str);
		}
		else
		{
			append_char(&result, *str);
			str++;
		}
	}
	return (result);
}
