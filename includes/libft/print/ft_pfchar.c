/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:22:00 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/30 18:30:16 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static void	handle_fmt(t_fmt *fmt)
{
	if (fmt->width > 1)
		fmt->offset = fmt->width - 1;
	fmt->len += fmt->offset + 1;
}

static void	handle_print(t_fmt *fmt, char c)
{
	if (fmt->minus)
		ft_putchar_fd(c, fmt->fd);
	ft_putlchar_fd(fmt->offset, ' ', fmt->fd);
	if (!fmt->minus)
		ft_putchar_fd(c, fmt->fd);
}

void	ft_pfchar(t_fmt *fmt, char c)
{
	handle_fmt(fmt);
	handle_print(fmt, c);
}

/*
	static void handle_fmt(t_fmt *fmt)
	{
		if (there's width) i.e ft_printf(%5c, c);
			then the offset = 4 whitespaces
		fmt->len += the offset + 1 
		we can't set it equal to the width + 1, or the width only.
		assume:
			1) ft_printf(%c, c)
				fmt->len	=> width + 1 = 0 + 1 = 1 (true)
				fmt->len	=> width     = 0 (false)
			2) ft_printf(%5c, c)
				fmt->len	=> width + 1 = 6 (false)
				fmt->len	=> width     = 5 (true)
		therefor we need to count the offset first,
		and if there's any then we add 1 for the char.
	}
*/
