/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 23:06:38 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/02 12:01:00 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static void	handle_pad_offset(t_fmt *fmt, int nbr, int len, int abslen)
{
	if (fmt->precision > abslen)
		fmt->pad = fmt->precision - abslen;
	else if (fmt->zero && fmt->width > abslen && !fmt->dot)
		fmt->pad = fmt->width - abslen;
	if (fmt->zero
		&& fmt->pad
		&& nbr < 0
		&& fmt->width > fmt->precision
		&& fmt->width < (fmt->pad + len))
		fmt->pad--;
	if (fmt->width > (fmt->pad + len))
		fmt->offset = fmt->width - fmt->pad - len;
}

static void	handle_flags(t_fmt *fmt, int nbr)
{
	if ((fmt->space || fmt->plus) && nbr >= 0 && ++fmt->len)
	{
		if (fmt->pad && !fmt->offset && fmt->width > fmt->precision)
			fmt->pad--;
		else if (fmt->offset)
			fmt->offset--;
	}
}

static void	handle_fmt(t_fmt *fmt, int nbr, int len, int abslen)
{
	handle_pad_offset(fmt, nbr, len, abslen);
	handle_flags(fmt, nbr);
	ft_reset_fmt(fmt, '0');
	fmt->len += fmt->pad + fmt->offset + len;
}

static void	handle_print(t_fmt *fmt, int nbr)
{
	if (fmt->dot && !fmt->precision && !nbr)
	{
		if (fmt->minus && fmt->plus)
			ft_putchar_fd('+', fmt->fd);
		if (fmt->width == 1 && !fmt->plus && !fmt->space)
			ft_putchar_fd(' ', fmt->fd);
		else if (fmt->width > 1)
			ft_putlchar_fd(fmt->offset + 1, ' ', fmt->fd);
		if (fmt->space)
			ft_putchar_fd(' ', fmt->fd);
		if (!fmt->minus && fmt->plus)
			ft_putchar_fd('+', fmt->fd);
		if ((fmt->width == 1 && fmt->plus)
			|| (!fmt->width && !fmt->precision)
			|| (fmt-> width == 1 && fmt->space))
			fmt->len--;
	}
	else
	{
		if (fmt->minus)
			ft_pfputnbr_base(fmt, nbr, 10);
		ft_putlchar_fd(fmt->offset, ' ', fmt->fd);
		if (!fmt->minus)
			ft_pfputnbr_base(fmt, nbr, 10);
	}
}

void	ft_pfint(t_fmt *fmt)
{
	int		nbr;
	size_t	len;

	nbr = va_arg(fmt->args, int);
	len = ft_intlen(nbr);
	if (nbr < 0)
		handle_fmt(fmt, nbr, (int)len, (int)len - 1);
	else
		handle_fmt(fmt, nbr, (int)len, (int)len);
	handle_print(fmt, nbr);
}

/*
	Notes:
		1) We must handle the padding first (the zeros).
			padding occurs due to precision or leading zero.
			1- precision (if the digits is < than len we add 0's).
			2- leading zeros
		2) The offset (the spaces) depends on the padding .
			we only get offset if width > pad + len.
		3) We handle the flags and how they effect everything else.
		4) assume: nbr1 = 12, len1 = 2 && nbr2 = -12, len2 = 3.
	
	static void	handle_pad_offset(t_fmt *fmt, int nbr, int len, int abslen)
	{
		**1: if (fmt->precision > abslen)
				fmt->pad = fmt->precision - abslen;
		Q1. why we target abslen instead of len?
		A1. 
			- printf("3.3d", nbr1) => (012)
			- printf("3.3d", nbr2) => (-012)
			if we use the len, first one will be correct and the 2nd wrong,
			therefor we must we use the abslen,
			(neglect the - sign when you are calculating padding)
		
		**2 else if (fmt->zero && fmt->width > abslen && !fmt->dot)
				fmt->pad = fmt->width - abslen;
		Q2. why else if and not if.
		A2. because if we have both leading 0 and dot (precision),
			the praiorty will go to the precision,
			so in case we don't have precision and we have
			leading zero then this is our case here.
			- fmt->zero: there's a leading 0 flag.
			- fmt->width > abslen: we have room for 0's.
			- !fmt->dot: this is so important
				i'm avoiding fmt->precision < len {"%03.2d", nbr1},
				here we have precision but it doesn't go under **1,
				yet it's a 0 flag so if we set padding,
				the result will be (012) and that's wrong,
				if there's leading zero + precision,
				the precision either goes under **1 or neglect pad	
				so here we must add !fmt->dot.
							
		**3 (fmt->zero
			&& fmt->pad
			&& nbr < 0
			&& fmt->width > fmt->precision
			&& fmt->width < (fmt->pad + len))
			- the whole idea here we don't enough room to print the digits with -
			- padd-- if nbr < 0 and there's 0 flag.
			- fmt->zero: if there's a leading 0 flag.
			- fmt->pad: if we got a pad in **1 || **2
				we don't want the pad to go in negative, 
				so we must check if we have pad or not.
			- nbr < 0: incase it's a negative value.
			- fmt->width > fmt->precision:
				this part used to handle the oppsite condition which is: 
				if (precision > width) don't reduce the pad, i.e. {"%03.7d", nbr}
			- fmt->width < (fmt->pad + len)
				we are checking the offset here,
				we must not have an offset.
				because if we do, it means we have enough room.
				i.e. {"%05.3d", nbr2}, we have offset == 1
				=> (-12) wrong result, => (-012) correct result

		**4 if (fmt->width > (fmt->pad + len))
			fmt->offset = fmt->width - fmt->pad - len;
				if we have padding and the min width required to print the nbr
				is > than the sum of pad + len, so we do have offset (spaces)
				to init the min required width.
	}

	static void	handle_flags(t_fmt *fmt, int nbr, int len)
	{
		if ((fmt->space || fmt->plus) && nbr >= 0 && ++fmt->len)
		- fmt->space || fmt->plus, if we have any of those
		- nbr >= 0:
			The space flag for positive numbers indicates 
				that a space should be used as the sign character.
			The space flag for negative numbers indicates 
				that the - sign will replace the space.
			So we are dealing only wih the cases where nbr >=0.
		- ++fmt->len: if we got here it means we are in the right case,
			so we increment the len by 1.
		- if (fmt->pad && !fmt->offset && fmt->width > fmt->precision)
			fmt->width > fmt->precision
			if false it means our precision > width (don't padd--)
		- else if (fmt->offset)
			fmt->offset--;
	}
	
	static void	handle_fmt(t_fmt *fmt, int nbr, int len, int abslen)
	{
		- ft_reset_fmt(fmt, '0');
			only to avoid the cases where offset || padding might goes
				in negative.
		- fmt->len += fmt->pad + fmt->offset + len;
			Here we used the len and not abslen, 
				because we need to include the sign if nbr < 0.
	}

	static void	handle_print(t_fmt *fmt, int nbr)
	{
		**5 if (fmt->dot && !fmt->width && !fmt->precision && !nbr)
				to handle cases such as: {"%.i", 0}, {"%.0i", 0}
				in these cases you won't print the 0
			if (fmt->minus && fmt->plus)
				ft_putchar_fd('+', 1);
				- left alignment and there's a + sign 
			if (fmt->width == 1 && !fmt->plus && !fmt->space)
				ft_putchar_fd(' ', 1);
				- we print space instead of 0
			else if (fmt->width > 1)
				ft_putlchar_fd(fmt->offset + 1, ' ', 1);
				- we print multiple spaces
			if (fmt->space)
				ft_putchar_fd(' ', 1);
			if (!fmt->minus && fmt->plus)
				ft_putchar_fd('+', 1);
			if ((fmt->width == 1 && fmt->plus)
				|| (!fmt->width && !fmt->precision)
				|| (fmt-> width == 1 && fmt->space))
				fmt->len--;
				line 33: if ((fmt->space || fmt->plus) ...., ++fmt->len)
					if there's + or space out fmt->len = 1
				line 47: fmt->len += fmt->pad + fmt->offset + len;
					the of nbr 0 = 1, out fmt->len = 2 at this point,
				so if we have a width == 1 && (+ || ' '),
				our fmt->len at this point = 2, so fmt->len--
				else if (!width && !precision) fmt->len-- also.
		**6 else if (fmt->dot && fmt->width && !fmt->precision && !nbr)
				to handle cases such as: {"%5.0i", 0}, {"%5.i", 0}
				in these cases you won't print the 0 but there's offset
				we add offset + 1 because our offset cal is widh - pad - len
				and since we wont print the 0 so we add 1 to the offset
	}
*/
