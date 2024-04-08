/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfmod.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 04:24:56 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/01 16:12:27 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static void	handle_fmt(t_fmt *fmt)
{
	if (fmt->width > 1)
		fmt->offset = fmt->width - 1;
	fmt->len += fmt->offset + 1;
}

static void	handle_print(t_fmt *fmt)
{
	if (fmt->minus)
		ft_putchar_fd('%', 1);
	ft_putlchar_fd(fmt->offset, ' ', fmt->fd);
	if (!fmt->minus)
		ft_putchar_fd('%', 1);
}

void	ft_pfmod(t_fmt *fmt)
{
	handle_fmt(fmt);
	handle_print(fmt);
}
