/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:21:38 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/28 20:13:59 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	parse_word(t_data *data, t_token *token)
{
	t_ast	*new_node;

	new_node = ast_new(data, token);
	if (!new_node)
		exit_failure(data);
	if (!data->ast)
		data->ast = new_node;
	else if (data->ast)
	{
		if (!data->ast->left && token->next && token->next->next)
			data->ast->left = new_node;
		else if (!data->ast->right)
			data->ast->right = new_node;
	}
}
/*
ls -la > file.txt | grep "drwxr" file.txt > file2.txt | wc -l && echo "done" && echo "success" && echo "yo" | sort | uniq
*/
