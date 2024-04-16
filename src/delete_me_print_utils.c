/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_me_print_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:57:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/15 20:59:25 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env_list(t_env *lst)
{
	while (lst)
	{
		printf("key: %s\nvalue: %s\n\n", lst->key, lst->value);
		lst = lst->next;
	}
}

void	print_tokens(t_token *lst)
{
	while (lst)
	{
		printf("\ntype: %d, value = %s\n\n", lst->type, lst->value);
		lst = lst->next;
	}
}

void	print_ast(t_ast *ast)
{
	if (ast)
	{
		printf("token: %d\n", ast->type);
		print_ast(ast->left);
		print_ast(ast->right);
	}
}

void	print_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		printf("path[%d]: %s\n", i, path[i]);
}

// ls -l | grep "file" > output.txt
