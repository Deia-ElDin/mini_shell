/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:25:17 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 11:25:56 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

/**
 * the purpose of this function is to get the type of the token
*/

int	token_type(char *token)
{
	if (*token == '\'')
		return (TOKEN_SINGLE_QUOTE);
	if (*token == '\"')
		return (TOKEN_DOUBLE_QUOTE);
	if (!ft_strcmp(token, "<<"))
		return (TOKEN_HEREDOC);
	if (!ft_strcmp(token, ">>"))
		return (TOKEN_APPEND);
	if (!ft_strcmp(token, "<"))
		return (TOKEN_REDIR_IN);
	if (!ft_strcmp(token, ">"))
		return (TOKEN_REDIR_OUT);
	if (!ft_strcmp(token, "|"))
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}
