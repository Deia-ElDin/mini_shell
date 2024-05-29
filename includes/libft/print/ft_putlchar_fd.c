/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 04:39:35 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/02 11:48:43 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_putlchar_fd(size_t len, char c, int fd)
{
	while (len-- > 0)
		ft_putchar_fd(c, fd);
}

/*
	while (len-- > 0)
		only to avoid if the len is a negative value.
*/
