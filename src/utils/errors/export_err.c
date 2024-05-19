/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:13:32 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/19 17:41:41 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_err(t_data *data, char *err)
{
	ft_putstr_fd(ERR_PROMPT, STDERR_FILENO);
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	data_status(data, 1);
}
