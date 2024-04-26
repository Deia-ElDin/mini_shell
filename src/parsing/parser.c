/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 14:27:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 07:27:34 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	parser(t_data *data)
{
	data->ast = ast_head(data, data->tokens, 'r');
	if (!data->ast)
		return (false);
	ast_add(data, data->ast, 'l');
	ast_add(data, data->ast, 'r');
	printf("\nast tree\n");
	print_ast(data->ast);
	return (true);
}

/*
ls -la > file.txt | grep "test" | wc -l && echo "done" && echo "success""yo"
1 > 2 | 3 && 4
*/

//Could we add all word tokens after the first word token
//since any word tokens after the first are considered input

//This could help keep all input together so it could be compiled into a 2d char
//array and given to execve in a much easier manner