/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:27:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/22 18:07:06 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static t_ast	*handle_cmd_redir(t_data *data, t_token *tokens, t_ast *head)
// {
// 	if (tokens->prev->type != TOKEN_REDIR_IN
// 		|| tokens->prev->type != TOKEN_REDIR_OUT)
// 		return (head);
// 	token_del_relink(&tokens->prev);
// 	token_del_relink(&tokens);
// 	return (head);
// }

/*
Find next highest token in the precedence and returns next head token
*/
static t_token	*get_next_left_node(t_data *data, t_token *tokens)
{
	t_token	*token_node;

	token_node = NULL;
	while (tokens)
	{
		if (tokens->type == data->next_high_token)
			token_node = tokens;
		tokens = tokens->prev;
	}
	if (!token_node && data->next_high_token >= 0)
	{
		data->next_high_token--;
		get_next_left_node(data, tokens);
	}
	return (token_node);
}

/*
Find next highest token in the precedence and returns next head token
*/
static t_token	*get_next_right_node(t_data *data, t_token *tokens)
{
	t_token	*token_node;

	token_node = NULL;
	while (tokens)
	{
		if (tokens->type == data->next_high_token)
			token_node = tokens;
		tokens = tokens->next;
	}
	if (!token_node && data->next_high_token >= 0)
	{
		data->next_high_token--;
		get_next_right_node(data, tokens);
	}
	return (token_node);
}

static int	recursive_parsing(t_data *data, t_token *token, t_ast *node)
{
	t_ast	*left_node;
	t_token	*left_token;
	t_ast	*right_node;
	t_token	*right_token;

	if (!token)
		return (1);
	left_token = get_next_left_node(data, token);
	left_node = new_ast(left_token->type);
	add_left_ast(&node, left_node);
	right_token = get_next_right_node(data, token);
	right_node = new_ast(right_token->type);
	add_right_ast(&node, right_node);
	recursive_parsing(data, left_token, left_node);
	recursive_parsing(data, right_token, right_node);
	return (0);
}

t_ast	*parser(t_data *data)
{
	t_ast	*head_node;
	t_token	*head_token;

	while (1)
	{
		if (data->tokens->prev == NULL)
			break ;
		data->tokens = data->tokens->prev;
	}
	printf("DEBUG head token (%d)\n", data->tokens->type);
	head_token = get_next_right_node(data, data->tokens);
	head_node = NULL;
	if (head_token)
		head_node = new_ast(head_token->type);
	if (!head_node || recursive_parsing(data, head_token, head_node))
		return (NULL);
	return (head_node);
}

//Could we add all word tokens after the first word token
//since any word tokens after the first are considered input

//This could help keep all input together so it could be compiled into a 2d char
//array and given to execve in a much easier manner
