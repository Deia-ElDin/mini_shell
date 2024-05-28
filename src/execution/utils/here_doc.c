/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:36:22 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/28 17:06:09 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_for_heredoc(t_data *data)
{
	t_ast	*ast;
	char	*str;
	char	*temp;

	ast = data->ast;
	if (ast->right->type != NODE_HEREDOC)
		return (0);
	temp = readline(NULL);
	str = "";
	while (ft_strcmp(temp, ast->right->file))
	{
		temp = readline(NULL);
		str = ft_strjoin(str, temp);
	}
	return (1);
}
