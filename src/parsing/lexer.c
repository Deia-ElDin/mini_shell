/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:08:25 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/16 15:57:17 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	get_type(char *token)
// {
// 	if (!ft_strcmp(token, "\'"))
// 		return (TOKEN_SINGLE_QUOTE);
// 	if (!ft_strcmp(token, "\""))
// 		return (TOKEN_DOUBLE_QUOTE);
// 	if (!ft_strcmp(token, "\\"))
// 		return (TOKEN_ESCAPE);
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
// 	if (!ft_strcmp(token, ";"))
// 		return (TOKEN_SEMIC);
// 	return (TOKEN_WORD);
// }

// t_token	*lexer(char *line)
// {
// 	char	**token_array;
// 	t_token	*token;
// 	t_token	*head;
// 	int		type;
// 	int		index;

// 	token = NULL;
// 	head = NULL;
// 	index = 0;
// 	token_array = ft_split(line, '|');
// 	if (!token_array)
// 		exit(1);
// 	while (token_array[index])
// 	{
// 		type = get_type(token_array[index]);
// 		token = new_token(type, token_array[index]);
// 		if (!token)
// 			exit(1);
// 		add_token(&head, token);
// 		index++;
// 	}
// 	ft_free(&token_array, 'a');
// 	return (head);
// }

// t_token	*new_token(int type, char *token_value)
// {
// 	t_token	*token;
// 	char	*value;

// 	if (!type || !token_value)
// 		return (NULL);
// 	value = ft_strdup(token_value);
// 	if (!value)
// 		exit(1);
// 	token = (t_token *)ft_calloc(1, sizeof(t_token));
// 	if (!token)
// 		exit(1);
// 	token->type = type;
// 	token->value = value;
// 	token->next = NULL;
// 	return (token);
// }

t_token	*lexer(t_data *data)
{
	t_token	*tokens;

	tokens = NULL;
	if (!(*data->line))
		return (NULL);
	tokens = create_tokens(data);
	print_tokens(tokens);
	return (tokens);
}
