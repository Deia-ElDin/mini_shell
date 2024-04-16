/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfuint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 22:12:11 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/02 11:42:16 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static void	handle_pad_offset(t_fmt *fmt, unsigned int nbr, int len)
{
	if (fmt->precision > len)
		fmt->pad = fmt->precision - len;
	else if (fmt->zero && fmt->width > len && !fmt->dot)
	{
		fmt->pad = fmt->width - len;
		if (fmt->hashtag && nbr != 0)
			fmt->pad -= 2;
	}
	if (fmt->width > fmt->pad + len)
		fmt->offset = fmt->width - fmt->pad - len;
}

static void	handle_flags(t_fmt *fmt, unsigned int nbr)
{
	if (fmt->hashtag && nbr > 0)
	{
		fmt->len += 2;
		if (fmt->offset > 0)
			fmt->offset -= 2;
	}
}

static void	handle_fmt(t_fmt *fmt, unsigned int nbr, int len)
{
	handle_pad_offset(fmt, nbr, len);
	handle_flags(fmt, nbr);
	ft_reset_fmt(fmt, '0');
	fmt->len += fmt->pad + fmt->offset + len;
}

static void	handle_print(t_fmt *fmt, unsigned int nbr, int base)
{
	if (fmt->dot && !fmt->precision && !nbr)
	{
		if (!fmt->width)
			fmt->len--;
		else
			ft_putlchar_fd(fmt->offset + 1, ' ', fmt->fd);
	}
	else
	{
		if (fmt->minus)
			ft_pfputnbr_base(fmt, nbr, base);
		ft_putlchar_fd(fmt->offset, ' ', fmt->fd);
		if (!fmt->minus)
			ft_pfputnbr_base(fmt, nbr, base);
	}
}

void	ft_pfunit(t_fmt *fmt, int base)
{
	unsigned int	nbr;
	size_t			len;

	nbr = va_arg(fmt->args, unsigned int);
	len = ft_uintlen_base(nbr, base);
	handle_fmt(fmt, nbr, (int)len);
	handle_print(fmt, nbr, base);
}

/*

	static void	handle_pad_offset(t_fmt *fmt, unsigned int nbr, int len)
	{
		if (fmt->hashtag && nbr != 0)
			fmt->pad -= 2;
			we are dealing with %x,
			such as ft_printf("42%0#24x42.\n", 1515196500);
	}

	**1 if (fmt->hashtag && nbr != 0)
		fmt->pad -= 2;
	VS
	**2 if (fmt->hashtag && nbr > 0)
	{
		fmt->len += 2;
		if (fmt->offset > 0 )
			fmt->offset -= 2;
	}
		**1 i'm dealing with zero flag condition (no offset)
		**2 i'm checking if there's an offset we reduce the offset by 2
		we are reducing the padding by 2 because we shouldn't print that much 0,
		it has nothing to do with this (fmt->offset -= 2;), because
		one way or another we will reduce the offset if there's,
		if there wasn't we already reduced the pad, 
		but if there was pad and offset, we already reduced the pad.
*/
