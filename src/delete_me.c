/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_me.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:57:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/28 19:50:43 by dehamad          ###   ########.fr       */
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
		printf("\n\ntype: %d\n", ast->type);
		printf("value: %s\n", ast->token->value);
		printf("index: %d\n", ast->token->index);
		if (ast->cmd)
			printf("cmd: %s\n", ast->cmd[0]);
		{
			printf("tree \n");
			if (ast->left)
				printf("left: %s, %d\n", ast->left->token->value, ast->left->token->index);
			else
				printf("left: NULL\n");
			if (ast->right)
				printf("right: %s, %d\n", ast->right->token->value, ast->right->token->index);
			else
				printf("right: NULL\n");
		}
		if (ast->left)
		{
			printf("\ngoing left: \n");
			printf("head: %s, %d\n", ast->token->value, ast->token->index);
			print_ast(ast->left);
		}
		if (ast->right)
		{
			printf("\ngoing right: \n");
			printf("head: %s, %d\n", ast->token->value, ast->token->index);
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
