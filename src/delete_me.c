/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_me.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:57:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 07:21:33 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env_array(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("env[%d]: %s\n", i, env[i]);
}

void	print_env_list(t_env *lst)
{
	while (lst)
	{
		printf("key %s\nvalue %s\n\n", lst->key, lst->value);
		lst = lst->next;
	}
}

void	print_tokens(t_token *lst)
{
	while (lst)
	{
		printf("\nindex: %d type: %d, value = .%s. space = %d\n",
			lst->index, lst->type, lst->value, lst->is_space);
		lst = lst->next;
	}
}

void	print_ast(t_ast *ast)
{
	if (ast)
	{
		printf("ast index: %d, type: %d, file = %s\n",
			ast->index, ast->type, ast->file);
		if (ast->left)
		{
			printf("\ngoing left\n");
			print_ast(ast->left);
		}
		if (ast->right)
		{
			printf("\ngoing right\n");
			print_ast(ast->right);
		}
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
