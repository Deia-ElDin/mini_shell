/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:43:25 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/18 18:44:47 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
// static char	**parse_commands(t_token *token, t_ast *node)
// {
// 	(void) node;
// 	char	**cmds;
// 	int		i;
// 	int	size;
		
// 	size = ft_strlen(token->value);
// 	i = 0;
// 	// ft_putstr_fd("token->value: ", 2);
// 	// ft_putstr_fd(token->value, 2);
// 	// ft_putstr_fd("\n", 2);
// 	cmds = (char **)ft_calloc((3), sizeof(char *));
// 	while (token->value[i] && token->value[i] != ' ')
// 		i++;
// 	cmds[0] = ft_substr(token->value, 0, i);
// 	cmds[1] = ft_substr(token->value, i + 1, size - i);
// 	cmds[2] = NULL;
// 	// if (token->value[ft_strlen(token->value) - 1] == ' ')
// 	// {
// 	// 	while (cmds[size])
// 	// 		size++;
// 	// 	node->cmd = (char **)ft_calloc((size + 2), sizeof(char *));
// 	// 	while (cmds[i])
// 	// 	{
// 	// 		node->cmd[i] = ft_strdup(cmds[i]);
// 	// 		i++;
// 	// 	}
// 	// 	node->cmd[i] = ft_strdup("");
// 	// 	node->cmd[i + 1] = NULL;
// 	// 	ft_free(&cmds, 'a');
// 	// 	cmds = node->cmd;
// 	// }
// 	return (cmds);
// }
=======
static char	**parse_commands(t_token *token, t_ast *node)
{
	(void) node;
	char	**cmds;
	int		i;
	int	size;
		
	size = ft_strlen(token->value);
	i = 0;
	// ft_putstr_fd("token->value: ", 2);
	// ft_putstr_fd(token->value, 2);
	// ft_putstr_fd("\n", 2);
	cmds = (char **)ft_calloc((3), sizeof(char *));
	while (token->value[i] && token->value[i] != ' ')
		i++;
	cmds[0] = ft_substr(token->value, 0, i);
	cmds[1] = ft_substr(token->value, i + 1, size - i);
	cmds[2] = NULL;
	// if (token->value[ft_strlen(token->value) - 1] == ' ')
	// {
	// 	while (cmds[size])
	// 		size++;
	// 	node->cmd = (char **)ft_calloc((size + 2), sizeof(char *));
	// 	while (cmds[i])
	// 	{
	// 		node->cmd[i] = ft_strdup(cmds[i]);
	// 		i++;
	// 	}
	// 	node->cmd[i] = ft_strdup("");
	// 	node->cmd[i + 1] = NULL;
	// 	ft_free(&cmds, 'a');
	// 	cmds = node->cmd;
	// }
	return (cmds);
}
>>>>>>> 8560f237e995b54c6ae69d2cb6f43f2bf9ad47ed

static int	check_heredoc_tokens(t_token *next, t_ast *right_node)
{
	t_heredoc	*heredoc;

	heredoc = (t_heredoc *)ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return (ft_putstr_fd("ERR\n", 2), -1);
	right_node->heredoc = heredoc;
	right_node->heredoc->exists = false;
	if (next && next->type == TOKEN_HEREDOC)
	{
		right_node->type = next->type - 2;
		if (next->next)
		{
			right_node->heredoc->exists = true;
			right_node->heredoc->stop_key = next->next->value;
			next->next->is_parsed = true;
		}
		else
			right_node->heredoc->file = NULL;
		next->is_parsed = true;
	}
	else
		return (0);
	return (1);
}

static void	check_redir_tokens(t_token *token, t_ast *right_node)
{
	t_token	*next;

	next = token->next;
	if (check_heredoc_tokens(next, right_node) && next->next)
		next = next->next->next;
	if (next && next->type < TOKEN_WORD)
	{
		right_node->type = next->type - 2;
		if (next->next)
		{
			right_node->file = next->next->value;
			next->next->is_parsed = true;
		}
		else
			right_node->file = NULL;
		next->is_parsed = true;
	}
	else
		right_node->type = NODE_WORD;
	right_node->cmd = ft_split(token->value, ' ');
}

t_ast	*parse_cmd(t_token *token, t_ast *new_node)
{
	t_ast	*left_node;
	t_ast	*right_node;

	left_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	right_node = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (!left_node || !right_node)
		exit(1);
	check_redir_tokens(token, right_node);
	right_node->end_flag = 0;
	right_node->left = NULL;
	right_node->right = NULL;
	right_node->head = new_node;
	left_node->end_flag = 0;
	left_node->type = NODE_WORD;
	left_node->cmd = (char **)ft_calloc(2, sizeof(char *));
	if (!left_node->cmd)
		return (NULL);
	left_node->cmd[0] = ft_strdup(right_node->cmd[0]);
	left_node->cmd[1] = NULL;
	left_node->left = NULL;
	left_node->right = NULL;
	left_node->head = new_node;
	new_node->left = left_node;
	new_node->right = right_node;
	return (new_node);
}

int	is_file(t_token *token)
{
	if (token->type != TOKEN_WORD)
		return (0);
	else if (token->prev && token->prev->type < TOKEN_WORD)
		return (1);
	else
		return (0);
}
