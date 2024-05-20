/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:27:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/20 15:20:19 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	parser(t_data *data)
{
	t_token	*token;

	token = data->tokens;
	while (token)
	{
		if (token->type == NODE_CMD || token->type == NODE_BUILTIN)
			parse_word(data, &token);
		else if (token->type == NODE_PIPE)
			parse_pipe(data, &token);
		else if (token->type == NODE_REDIR_IN || token->type == NODE_REDIR_OUT
			|| token->type == NODE_APPEND || token->type == NODE_HEREDOC)
			parse_redirection(data, &token);
		else
			token = token->next;
	}
	print_ast(data->ast);
	return (data->ast != NULL);
}

// bool	parser(t_data *data)
// {
// 	t_token	*token;

// 	token = data->tokens;
// 	while (token)
// 	{
// 		ast_tree(data, token);
// 		token = token->next;
// 	}
// 	print_ast(data->ast);
// 	if (data->ast)
// 		return (true);
// 	return (false);
// }
/*
ls -la > file2.txt | grep "drwxr" file2.txt >> file2.txt | wc -l && echo "done" && echo "success" && echo "yo" | sort | uniq
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
