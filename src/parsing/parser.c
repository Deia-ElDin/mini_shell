/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:27:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/29 22:51:33 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	t_ast	*node_values(t_data *data, t_ast *new_node, t_token *token)
{
	char	*ptr;

	new_node->type = token->type;
	if (token->type == TOKEN_WORD)
	{
		ptr = ft_strdup(token->value);
		if (!ptr)
			exit_failure(data);
		new_node->cmd = ft_split(ptr, ' ');
		if (!new_node->cmd)
			exit_failure(data);
	}
	else
		new_node->cmd = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->token = token;
	token->is_taken = true;
	return (new_node);
}

t_ast	*ast_new(t_data *data, t_token *token)
{
	t_ast	*new_node;

	if (!data || !token)
		return (NULL);
	new_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		exit_failure(data);
	return (node_values(data, new_node, token));
}
void	ast_tree(t_data *data, t_token *token)
{
	t_ast	*new_node;

	new_node = ast_new(data, token);
	if (!new_node)
		exit_failure(data);
	data->ast = data->ast;
	if (!data->ast)
		data->ast = new_node;
	else if (token->type == TOKEN_WORD)
	{
		if (!data->ast->left && token->next && token->next->next)
			data->ast->left = new_node;
		else if (!data->ast->right)
			data->ast->right = new_node;
	}
	else
	{
		new_node->left = data->ast;
		data->ast = new_node;
	}
}

bool	parser(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	while (token)
	{
		ast_tree(data, token);
		token = token->next;
	}
	print_ast(data->ast);
	return (true);
}
/*
ls -la > file.txt | grep "drwxr" file.txt > file2.txt | wc -l && echo "done" && echo "success" && echo "yo" | sort | uniq
*/

/*
index: 0 type: 2, value = .ls -la. space = 1
index: 1 type: 4, value = .>. space = 1
index: 2 type: 2, value = .file.txt. space = 1
index: 3 type: 7, value = .|. space = 1
index: 4 type: 2, value = .grep drwxr file.txt. space = 1
index: 5 type: 4, value = .>. space = 1
index: 6 type: 2, value = .file2.txt. space = 1
index: 7 type: 7, value = .|. space = 1
index: 8 type: 2, value = .wc -l. space = 1
index: 9 type: 9, value = .&&. space = 1
index: 10 type: 2, value = .echo done. space = 1
index: 11 type: 9, value = .&&. space = 1
index: 12 type: 2, value = .echo success. space = 1
index: 13 type: 9, value = .&&. space = 1
index: 14 type: 2, value = .echo yo. space = 1
index: 15 type: 7, value = .|. space = 1
index: 16 type: 2, value = .sort. space = 1
index: 17 type: 7, value = .|. space = 1
index: 18 type: 2, value = .uniq. space = 0
*/

// bool	parser(t_data *data)
// {
// 	t_token	*token;

// 	token = data->tokens;
// 	while (token)
// 	{
// 		if (token->type == TOKEN_WORD)
// 			parse_word(data, token);
// 		else if (token->type == TOKEN_PIPE)
// 			parse_pipe(data, token);
// 		else if (token->type == TOKEN_REDIR_IN)
// 			parse_redir_in(data, token);
// 		else if (token->type == TOKEN_REDIR_OUT)
// 			parse_redir_out(data, token);
// 		else if (token->type == TOKEN_APPEND)
// 			parse_append(data, token);
// 		else if (token->type == TOKEN_HEREDOC)
// 			parse_heredoc(data, token);
// 		else if (token->type == TOKEN_AND)
// 			parse_and(data, token);
// 		else if (token->type == TOKEN_OR)
// 			parse_and(data, token);
// 		token = token->next;
// 	}
// }



// bool	parser(t_data *data)
// {
// 	data->ast = head(data, NULL);
// 	if (!data->ast)
// 		return (false);
// 	ast_add(data, data->ast, 'l');
// 	// ast_add(data, data->ast, 'r');
// 	printf("\nast tree\n");
// 	print_ast(data->ast);
// 	return (true);
// }

// add a flag to the and node and or node and all nodes 3shan omran

/*
ls -la > file.txt | grep "drwxr" file.txt > file2.txt | wc -l && echo "done" && echo "success" && echo "yo" | sort | uniq




1 > 2 | 3 && 4
*/

//Could we add all word tokens after the first word token
//since any word tokens after the first are considered input

//This could help keep all input together so it could be compiled into a 2d char
//array and given to execve in a much easier manner

/*
ls -la > file.txt && grep total file.txt | wc -l && echo "done" && echo "success" && echo "yo" | sort | uniq
*/

// static	bool	is_special_token(t_token *token)
// {
// 	if (!token)
// 		return (false);
// 	if (token->type == TOKEN_AND || token->type == TOKEN_OR
// 		|| token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
// 		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC
// 		|| token->type == TOKEN_PIPE)
// 		return (true);
// 	return (false);
// }

// // t_ast	*ast_branch(t_data *data, t_token *token)
// // {
// // 	t_ast	*head;

// // 	if (!token || (!token->prev && !token->next))
// // 		return (NULL);
// // 	head = ast_new(data, token);
// // 	if (!head)
// // 		exit_failure(data);
// // 	if (token->prev)
// // 	{
// // 		head->left = ast_new(data, token->prev);
// // 		if (!head->left)
// // 			exit_failure(data);
// // 	}
// // 	if (token->next)
// // 	{
// // 		head->right = ast_new(data, token->next);
// // 		if (!head->right)
// // 			exit_failure(data);
// // 	}
// // 	return (head);
// // }

// bool

// bool	is_left_sided(t_token *token)
// {
// 	if (!token || (!token->prev && !token->next))
// 		return (false);
// 	if (token->prev)
// 		return (token->type >= token->prev->type);
// 	if (token->next)
// 		return (token->type <= token->next->type);
// }

// t_ast	*ast_attach(t_data *data, t_ast *head, t_token *token)
// {
// 	t_ast	*new_node;

// 	new_node = ast_new(data, token);
// 	if (!new_node)
// 		exit_failure(data);
// 	if (is_pre(token))
// 	{
// 		new_node->left = head;
// 		head = new_node;
// 	}
// 	else if (is_post(token))
// 	{
// 		new_node->right = head;
// 		head = new_node;
// 	}
// 	return (head);
// }

// void	parse_word(t_data *data, t_token *token)
// {
// 	t_ast	*new_node;
// 	t_ast	*new_head;

// 	if (!token)
// 	{
// 		printf("we are in trouble\n");
// 		return ;
// 	}
// 	new_node = ast_new(data, token);
// 	if (!new_node)
// 		exit_failure(data);
// 	if (!token->index)
// 		data->ast = new_node;
// 	else if (is_special_token(token->prev) && (is_pre(token) || is_post(token)))
// 	{
// 		if (is_pre(token))
// 			data->ast->left = new_node;
// 		else if (is_post(token))
// 			data->ast->right = new_node;
// 	}
// 	else if ()
// 	{
// 		new_node->left = data->ast;
// 		data->ast = new_node;
// 	}
// }

// void	parse_pipe(t_data *data, t_token *token)
// {
// 	t_ast	*new_node;

// 	new_node = ast_new(data, token, '|');
// 	if (!ast)
// 		return ;
// 	ast_add(data, ast, 'l');
// 	ast_add(data, ast, 'r');
// }



// static	bool	is_special_token(t_token *token)
// {
// 	if (!token)
// 		return (false);
// 	if (token->type == TOKEN_AND || token->type == TOKEN_OR
// 		|| token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT
// 		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC
// 		|| token->type == TOKEN_PIPE)
// 		return (true);
// 	return (false);
// }

// static	bool	is_match(t_data *data, t_token *token)
// {
// 	if (!token)
// 		return (false);
// 	if (token->type == data->highest_token)
// 		return (true);
// 	return (false);
// }

// static t_token	*token_get(t_data *data, t_ast *head)
// {
// 	t_token	*token;

// 	if (!head)
// 		token = token_last(data);
// 	else
// 		token = head->token->prev;
// 	while (token)
// 	{
// 		if (is_special_token(token) && is_match(data, token))
// 			return (token);
// 		token = token->prev;
// 	}
// 	return (NULL);
// }

// t_ast	*head(t_data *data, t_ast *head)
// {
// 	t_token	*token;

// 	token = NULL;
// 	data->highest_token = TOKEN_AND;
// 	while (data->highest_token >= 3)
// 	{
// 		token = token_get(data, head);
// 		if (token)
// 			break ;
// 		data->highest_token--;
// 	}
// 	return (ast_new(data, token));
// }