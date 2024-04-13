/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:42:27 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/13 14:29:31 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*new_token(int type, char *line)
{
	t_token	*token;
	char	*value;

	if (!line || !*line || !type)
		return (NULL);
	if (type == TOKEN_DOUBLE_REDIR_IN || type == TOKEN_DOUBLE_REDIR_OUT)
		value = ft_strdup_n(line, 2);
	else
		value = ft_strdup_n(line, 1);
	if (!value)
		exit(1);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		exit(1);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	if (!*head)
		*head = new_token;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
	return (new_token);
}

void	free_tokens(t_data *data, t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
	data->tokens = NULL;
}
