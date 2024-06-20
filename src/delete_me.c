/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_me.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:57:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/20 18:29:18 by dehamad          ###   ########.fr       */
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
	int	i;

	if (ast)
	{
		// printf("type: %d\n", ast->type);
		printf("\nhead => type = %d ", ast->type);
		if (ast->head)
			printf("current nodes head type => %d", ast->head->type);
		printf("\n");
		if (ast->cmd)
		{
			i = -1;
			while (ast->cmd[++i])
				printf("cmd[%d]: %s\n", i, ast->cmd[i]);
		}
		printf("\n");
		if (ast->left && ast->left->head)
			printf("	left => type = %d nodes head type => %d\n", ast->left->type, ast->left->head->type);
		if (ast->right && ast->right->head)
			printf("	right => type = %d nodes head type => %d\n", ast->right->type, ast->right->head->type);
		if (ast->left)
		{
			printf("\nGoing left ---> \n");
			print_ast(ast->left);
		}
		if (ast->right)
		{
			printf("\nGoing right ---> \n");
			print_ast(ast->right);
		}
	}
	else
		printf("AST FAILED\n");
}

void	print_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i])
		printf("path[%d]: %s\n", i, path[i]);
}

// ls -l | grep "file" > output.txt
