/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:29:53 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 05:02:04 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/// @brief Used to print a syntax error
/// @param err The error message
void	syntax_error(char *err)
{
	ft_putstr_fd(ERR_PROMPT, STDERR_FILENO);
	ft_putstr_fd(SYNTAX_ERR, STDERR_FILENO);
	ft_putstr_fd(" `", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

