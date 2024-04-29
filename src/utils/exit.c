/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:01:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/26 05:45:32 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_success(t_data *data)
{
	data_free(data);
	exit(EXIT_SUCCESS);
}

void	exit_failure(t_data *data)
{
	data_free(data);
	exit(EXIT_FAILURE);
}
