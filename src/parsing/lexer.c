/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:08:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/13 14:29:31 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	is_redirection(char c1, char c2)
{
	if (c1 == '<' && c2 == '<')
		return (TOKEN_DOUBLE_REDIR_IN);
	if (c1 == '>' && c2 == '>')
		return (TOKEN_DOUBLE_REDIR_OUT);
	if (c1 == '<')
		return (TOKEN_REDIR_IN);
	if (c1 == '>')
		return (TOKEN_REDIR_OUT);
	return (0);
}

static int	is_pipe(char c)
{
	return (c == '|');
}

static int	is_escape(char c)
{
	return (c == '\\');
}

t_token	*lexer(char *line)
{
	t_token	*token;
	t_token	*head;
	int		type;

	token = NULL;
	head = NULL;
	while (*line)
	{
		if (is_quote(*line))
			type = TOKEN_QUOTE;
		else if (is_escape(*line))
			type = TOKEN_ESCAPE;
		else if (is_redirection(*line, *(line + 1)))
			type = is_redirection(*line, *(line + 1));
		else if (is_pipe(*line))
			type = TOKEN_PIPE;
		else
			type = 0;
		if (type)
		{
			token = new_token(type, line);
			if (!token)
				exit(1);
			add_token(&head, token);
			if (type == TOKEN_DOUBLE_REDIR_IN || type == TOKEN_DOUBLE_REDIR_OUT)
				line++;
		}
		line++;
	}
	return (head);
}
