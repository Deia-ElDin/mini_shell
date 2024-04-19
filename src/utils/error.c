/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:29:53 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/19 20:44:58 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(char *err)
{
	ft_putstr_fd(ERR_PROMPT, STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
}
