/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:42:27 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/16 16:20:21 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	get_type(char *token)
{
	if (!ft_strcmp(token, "\'"))
		return (TOKEN_SINGLE_QUOTE);
	if (!ft_strcmp(token, "\""))
		return (TOKEN_DOUBLE_QUOTE);
	if (!ft_strcmp(token, "\\"))
		return (TOKEN_ESCAPE);
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
	return (TOKEN_WORD);
}

t_token	*new_token(t_data *data, int start, int len)
{
	t_token	*token;
	char	*value;

	if (!data->line || !len)
		return (NULL);
	value = ft_substr(data->line, start, len);
	if (ft_isempty_str(value))
		return (ft_free(&value, 'p'), NULL);
	if (!value)
		exit_failure(data);
	// printf("value: %s\n", value);
	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		exit_failure(data);
	token->type = get_type(value);
	token->value = ft_strtrim(value, WHITESPACES);
	token->next = NULL;
	free(value);
	return (token);
}

t_token	*add_token(t_token **head, t_token *new_token)
{
	t_token	*tmp;

	// printf("new_token->value: %s\n", new_token->value);
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

t_token	*create_tokens(t_data *data)
{
	int		i;
	int		start;
	t_token	*token;
	t_token	*head;

	i = -1;
	start = 0;
	token = NULL;
	head = NULL;
	if (!*data->line)
		return (NULL);
	while (data->line[++i])
	{
		if (ft_strchr(" |><", data->line[i]))
		{
			if (data->line[i] == ' ')
				add_token(&head, new_token(data, start, i - start));
			else if (data->line[i] == '|')
			{
				add_token(&head, new_token(data, start, i - start));
				add_token(&head, new_token(data, i, 1));
			}
			else if (data->line[i] == '>' && data->line[i + 1] == '>')
			{
				add_token(&head, new_token(data, start, i - start));
				add_token(&head, new_token(data, i++, 2));
			}
			else if (data->line[i] == '<' && data->line[i + 1] == '<')
			{
				add_token(&head, new_token(data, start, i - start));
				add_token(&head, new_token(data, i, 2));
			}
			else if (data->line[i] == '>')
			{
				add_token(&head, new_token(data, start, i - start));
				add_token(&head, new_token(data, i, 1));
			}
			else if (data->line[i] == '<')
			{
				add_token(&head, new_token(data, start, i - start));
				add_token(&head, new_token(data, i, 1));
			}
			start = i + 1;
		}
		if (!data->line[i + 1])
			add_token(&head, new_token(data, start, i - start + 1));
	}
	return (head);
}

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