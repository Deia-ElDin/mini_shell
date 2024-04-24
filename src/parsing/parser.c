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
static t_token	*get_next_left_node(t_data *data, t_token tokens)
{
	t_token	*token_node;
	t_token	*nav_token;

	nav_token = &tokens;
	token_node = NULL;
	while (nav_token)
	{
		if (nav_token->type == data->next_high_token)
			token_node = nav_token;
		nav_token = nav_token->prev;
	}
	if (!token_node && data->next_high_token >= 0)
	{
		data->next_high_token--;
		return (get_next_left_node(data, tokens));
	}
	return (token_node);
}

/*
Find next highest token in the precedence and returns next head token
*/
static t_token	*get_next_right_node(t_data *data, t_token tokens)
{
	t_token	*token_node;
	t_token	*nav_token;

	nav_token = &tokens;
	token_node = NULL;
	while (nav_token)
	{
		if (nav_token->type == data->next_high_token)
			token_node = nav_token;
		nav_token = nav_token->next;
	}
	if (!token_node && data->next_high_token > 0)
	{
		data->next_high_token--;
		return (get_next_right_node(data, tokens));
	}
	return (token_node);
}

static int	recursive_parsing(t_data *data, t_token token, t_ast node)
{
	t_ast	*new_node;
	t_token	*new_token;

	new_token = get_next_left_node(data, token);
	if (new_token)
		new_node = new_ast(new_token->type);
	if (new_node)
		add_left_ast(&node, new_node);
	if (new_node && new_token)
		if (recursive_parsing(data, *new_token, *new_node))
			return (1);
	new_token = get_next_right_node(data, token);
	if (new_token)
		new_node = new_ast(new_token->type);
	if (new_node)
		add_right_ast(&node, new_node);
	if (new_node && new_token)
		if (recursive_parsing(data, *new_token, *new_node))
			return (1);
	return (0);
}

t_ast	*parser(t_data *data)
{
	t_ast	*head_node;
	t_token	*head_token;

	if (!data)
		return (NULL);
	while (1)
	{
		if (data->tokens->prev == NULL)
			break ;
		data->tokens = data->tokens->prev;
	}
	head_token = get_next_right_node(data, *data->tokens);
	printf("DEBUG head token (%p)\n", head_token);
	head_node = NULL;
	if (head_token)
		head_node = new_ast(head_token->type);
	if (!head_node || recursive_parsing(data, *head_token, *head_node))
		return (NULL);
	return (head_node);
}

//Could we add all word tokens after the first word token
//since any word tokens after the first are considered input

//This could help keep all input together so it could be compiled into a 2d char
//array and given to execve in a much easier manner
