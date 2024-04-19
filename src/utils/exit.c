/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:01:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/19 22:24:31 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_success(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	exit_failure(t_data *data)
{
	free_data(data);
	exit(EXIT_FAILURE);
}
