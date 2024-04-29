/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:27:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/29 23:32:28 by dehamad          ###   ########.fr       */
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
	if (data->ast)
		return (true);
	return (false);
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
