/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:42:27 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/17 03:43:45 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	get_type(char *token)
{
	if (*token == '\'')
		return (TOKEN_SINGLE_QUOTE);
	if (*token == '\"')
		return (TOKEN_DOUBLE_QUOTE);
	if (!ft_strcmp(token, "<<"))
		return (TOKEN_HEREDOC);
	if (!ft_strcmp(token, ">>"))
		return (TOKEN_APPEND);
	if (!ft_strcmp(token, "<"))
		return (TOKEN_REDIR_IN);
	if (!ft_strcmp(token, ">"))
		return (TOKEN_REDIR_OUT);
	if (!ft_strcmp(token, "|"))
		return (TOKEN_PIPE);
	if (!ft_strcmp(token, ";"))
		return (TOKEN_SEMIC);
	if (!ft_strcmp(token, "\\"))
		return (TOKEN_ESCAPE);
	return (TOKEN_WORD);
}

static t_token	*new_token(t_data *data, int start, int len)
{
	t_token	*token;
	char	*value;

	token = NULL;
	if (!data->line || !len)
		return (NULL);
	value = ft_substr(data->line, start, (size_t)len);
	if (ft_isempty_str(value) || !*value)
		return (ft_free(&value, 'p'), NULL);
	if (!value)
		exit_failure(data);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		exit_failure(data);
	token->type = get_type(value);
	token->value = ft_strtrim(value, WHITESPACES);
	token->next = NULL;
	ft_free(&value, 'p');
	if (!token->value)
		exit_failure(data);
	return (token);
}

static void	add_token(t_data *data, t_token **head, int start, int len)
{
	t_token	*token;
	t_token	*tmp;

	token = new_token(data, start, len);
	if (!token)
		return ;
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!*head)
		*head = token;
	else
		tmp->next = token;
}

static void	create_tokens_recursively(t_data *data, t_token **head, int start)
{
	int	i;

	i = start;
	while (data->line[i] && !ft_strchr(" |><\"\'", data->line[i]))
		i++;
	add_token(data, head, start, i - start);
	if (!data->line[i])
		return ;
	if (ft_isdouble_redirect(&(data->line[i])))
		add_token(data, head, i++, 2);
	else if (ft_strchr(" |><", data->line[i]))
		add_token(data, head, i, 1);
	else if (ft_isquote(data->line[i]))
	{
		start = i;
		while (data->line[++i] && data->line[i] != data->line[start])
			;
		add_token(data, head, start, i - start + 1);
	}
	create_tokens_recursive(data, head, i + 1);
}

t_token	*create_tokens(t_data *data)
{
	t_token	*head;

	head = NULL;
	create_tokens_recursive(data, &head, 0);
	return (head);
}

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
//ls -l|a>b<c>>d<<e | f 
// echo hi >"file1   |'|||  iknj jnjnj kmk'''''''><><><><>>>>>>>"
// int quotes(char *str)
// {
// 	int i = 0;
// 	int flag = 0;
// 	while (str[i])
// 	{
// 		if(str[i] == '\'' || str[i] == '\"')
// 			flag = str[i];
// 		else if(str[i] == flag)
// 			flag = 0;
// 		if(str[i] == '>' && flag == 0)
// 			execve();
// 		i++;
// 	}
// }



//ls -l|a>b<c>>d<<e | f 
// echo hi >"file1   |'|||  iknj jnjnj kmk'''''''><><><><>>>>>>>"
// int quotes(char *str)
// {
// 	int i = 0;
// 	int flag = 0;
// 	while (str[i])
// 	{
// 		if(str[i] == '\'' || str[i] == '\"')
// 			flag = str[i];
// 		else if(str[i] == flag)
// 			flag = 0;
// 		if(str[i] == '>' && flag == 0)
// 			execve();
// 		i++;
// 	}
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