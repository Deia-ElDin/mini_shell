#include "../../includes/minishell.h"

int	and_operator(t_ast *ast, t_data *data)
{
	int	status1;
	int	status2;

	if (ast->left->left || ast->left->right)
		status1 = exec_ast(ast->left, data);
	if (ast->right->left || ast->right->right)
		status2 = exec_ast(ast->right, data);
	if (status1)
		return (status1);
	else if (status2)
		return (status2);
	else
		return (0);
}

int	or_operator(t_ast *ast, t_data *data)
{
	int	status1;
	int	status2;

	if (ast->left->left || ast->left->right)
		status1 = exec_ast(ast->left, data);
	if (ast->right->left || ast->right->right)
		status2 = exec_ast(ast->right, data);
	if (status1 && status2)
		return (status2);
	else
		return (0);
}