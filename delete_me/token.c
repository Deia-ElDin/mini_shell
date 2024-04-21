/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:42:27 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 20:22:48 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../../includes/minishell.h"

/**
 * The purpose of this function is to get the token type
*/

// static int	get_token_type(char *token)
// {
// 	if (*token == '\'')
// 		return (TOKEN_SINGLE_QUOTE);
// 	if (*token == '\"')
// 		return (TOKEN_DOUBLE_QUOTE);
// 	if (!ft_strcmp(token, "<<"))
// 		return (TOKEN_HEREDOC);
// 	if (!ft_strcmp(token, ">>"))
// 		return (TOKEN_APPEND);
// 	if (!ft_strcmp(token, "<"))
// 		return (TOKEN_REDIR_IN);
// 	if (!ft_strcmp(token, ">"))
// 		return (TOKEN_REDIR_OUT);
// 	if (!ft_strcmp(token, "|"))
// 		return (TOKEN_PIPE);
// 	return (TOKEN_WORD);
// }

// static t_token	*new_token(t_data *data, unsigned int start, int len)
// {
// 	t_token	*token;
// 	char	*value;

// 	token = NULL;
// 	if (!data->line || !len)
// 		return (NULL);
// 	value = ft_substr(data->line, start, (size_t)len);
// 	if (!value)
// 		exit_failure(data);
// 	if (ft_isempty_str(value))
// 		return (ft_free(&value, 'p'), NULL);
// 	token = (t_token *)ft_calloc(1, sizeof(t_token));
// 	if (!token)
// 		exit_failure(data);
// 	token->type = get_token_type(value);
// 	token->value = ft_strtrim(value, WHITESPACES);
// 	token->next = NULL;
// 	ft_free(&value, 'p');
// 	if (!token->value)
// 		exit_failure(data);
// 	return (token);
// }

/**
 * The purpose of this function is to add a token to the linked list
 * we create a new token
 * we loop over the linked list to get the last token
 * if the head is NULL we set the head to the token
 * else we set the last token next to the new token
*/

// static void	add_token(t_data *data, t_token **head, int start, int len)
// {
// 	t_token	*token;
// 	t_token	*tmp;

// 	token = new_token(data, start, len);
// 	if (!token)
// 		return ;
// 	tmp = *head;
// 	while (tmp && tmp->next)
// 		tmp = tmp->next;
// 	if (!*head)
// 		*head = token;
// 	else
// 		tmp->next = token;
// }

/**
 * The purpose of this function is to create the tokens (recursively)
 * we loop over the line till we find a special char
 * if we find a special char we create an add the token to the linked list
 * then we check the different cases i.e (>>, <<, >, <, |, " ", ' ')
 * if we find any of them we create and add the token to the linked list
 * unless if it was a quote we loop over the line till we find the closing quote
 * then we create and add the token to the linked list
*/

// void	create_tokens(t_data *data, t_token **head, unsigned int start)
// {
// 	unsigned int	i;

// 	i = start;
// 	while (data->line[i] && !ft_strchr(" |><\"\'", data->line[i]))
// 		i++;
// 	add_token(data, head, start, i - start);
// 	if (!data->line[i])
// 		return ;
// 	if (ft_isdouble_redirect(&(data->line[i])))
// 		add_token(data, head, i++, 2);
// 	else if (ft_strchr(" |><", data->line[i]))
// 		add_token(data, head, i, 1);
// 	else if (ft_isquote(data->line[i]))
// 	{
// 		start = i;
// 		while (data->line[++i] && data->line[i] != data->line[start])
// 			;
// 		add_token(data, head, start, i - start + 1);
// 	}
// 	create_tokens(data, head, i + 1);
// }

// t_token	*create_tokens(t_data *data)
// {
// 	int		i;
// 	int		start;
// 	t_token	*head;
// 	i = -1;
// 	start = 0;
// 	head = NULL;
// 	while (data->line[++i])
// 	{
// 		if (ft_strchr(" |>< \"\'", data->line[i]))
// 		{
// 			if (ft_isquote(data->line[i]))
// 			{
// 				start = i;
// 				while (data->line[++i] && data->line[i] != data->line[start])
// 					;
// 				add_token(data, &head, start, i - start + 1);
// 			}
// 			else if (ft_isspace(data->line[i]))
// 				add_token(data, &head, start, i - start);
// 			else if (ft_isdouble_redirect(&(data->line[i])))
// 			{
// 				add_token(data, &head, start, i - start);
// 				add_token(data, &head, i++, 2);
// 			}
// 			else if (ft_ispipe(data->line[i]) || ft_isredirect(data->line[i]))
// 			{
// 				add_token(data, &head, start, i - start);
// 				add_token(data, &head, i, 1);
// 			}
// 			start = i + 1;
// 		}
// 		else
// 		{
// 			while (data->line[i] && !ft_strchr(" |>< \"\'", data->line[i]))
// 				i++;
// 			add_token(data, &head, start, i - start);
// 			start = i--;
// 		}
// 		if (!data->line[i + 1] && i >= start)
// 			add_token(data, &head, start, i - start + 1);
// 	}
// 	return (head);
// }

// while (data->line[++i] && data->line[i] != data->line[start])
// {
// 	if (data->line[i] == '\\' && data->line[i + 1])
// 	i++;
// }

// void tokenize(char *line, t_token **token)
// {
// 	size_t i = 0;

// 	if (quote)
// 	{
// 		// take everything until next quote.
// 	}
// 	else
// 	{
// 		while (not_special)
// 		i++;
// 	}
// 	add_token(ft_substr(original, 0, i));
// 	tokenize(line + i, token);
// }