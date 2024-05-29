/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 22:34:36 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/02 19:59:31 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_reset_fmt(t_fmt *fmt, char type)
{
	if (type == '0')
	{
		if (fmt->offset < 0)
			fmt->offset = 0;
		if (fmt->pad < 0)
			fmt->pad = 0;
	}
	else if (type == 'r')
	{
		fmt->hashtag = 0;
		fmt->space = 0;
		fmt->plus = 0;
		fmt->pad = 0;
	}
}

void	ft_pfputnbr_base(t_fmt *fmt, long long nbr, int base)
{
	int		sign;
	char	*digits;

	sign = 1;
	digits = "0123456789abcdef";
	if (fmt->upper)
		digits = "0123456789ABCDEF";
	if (nbr < 0)
	{
		ft_putchar_fd('-', fmt->fd);
		sign = -1;
	}
	else if (nbr > 0 && fmt->hashtag && fmt->upper)
		ft_putstr_fd("0X", fmt->fd);
	else if (nbr > 0 && fmt->hashtag && !fmt->upper)
		ft_putstr_fd("0x", fmt->fd);
	else if (fmt->space)
		ft_putchar_fd(' ', fmt->fd);
	else if (fmt->plus)
		ft_putchar_fd('+', fmt->fd);
	ft_putlchar_fd(fmt->pad, '0', fmt->fd);
	ft_reset_fmt(fmt, 'r');
	if (nbr / base)
		ft_pfputnbr_base(fmt, sign * (nbr / base), base);
	ft_putchar_fd(digits[sign * (nbr % base)], fmt->fd);
}

/*
	void	init_reset_fmt(t_fmt *fmt, char target)
	{
		if (target == '0')
			the purpose of this if during our calculations for the pad or offset,
			and we decrement any of them to a value below 0,
			that will effect the len, so we need to make sure that they are >= 0.
			
		else if (target == 'r')
			the purpose of this is to rest the flags after applying them in 
			ft_pfputnbr_base, so for the 2nd call, we don't print the leading
			zeros or the spaces twice.
		
	}

	void	ft_pfputnbr_base(t_fmt *fmt, int nbr, int base)
	{
		The printing sequence as follow:
			1) - sign (if the nbr < 0)
			2) 0x    
			3) leading space 
			4) + sign
			5) padding
			depending on whatever we are printing we will follow that sequence
	}
*/
