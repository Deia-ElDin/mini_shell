/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:51:43 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/01 15:27:02 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static void	handle_fmt(t_fmt *fmt, int len)
{
	if (!fmt->dot || fmt->precision > len)
		fmt->precision = (int)len;
	if (fmt->width > fmt->precision)
		fmt->offset = fmt->width - fmt->precision;
	fmt->len += fmt->offset + fmt->precision;
}

static void	handle_print(t_fmt *fmt, char *str)
{
	if (fmt->minus)
		ft_putlstr_fd(str, fmt->precision, fmt->fd);
	ft_putlchar_fd(fmt->offset, ' ', fmt->fd);
	if (!fmt->minus)
		ft_putlstr_fd(str, fmt->precision, fmt->fd);
}

void	ft_pfstr(t_fmt *fmt)
{
	char	*str;
	size_t	len;

	str = va_arg(fmt->args, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	handle_fmt(fmt, (int)len);
	handle_print(fmt, str);
}

/*
	NOTE: 
		1) We are counting on fmt->precision at all times
	 		to print the str using ft_putlstr_fd().
		2) The offset is a result of a width > (precision || len).

	static void handle_fmt(t_fmt *fmt, int len)
	{
		if (!fmt->dot || fmt->precision > len)
			fmt->precision = len;
			assume:
				1) char *str = "123", len = 3, ft_printf("%5s", str);  
					=> !fmt->dot             => fmt->precision = 3;
				2) char *str = "123", len = 3, ft_printf("%5.5s", str);
					=> fmt->precision > len) => fmt->precision = 3;

		if (fmt->width > len)
			fmt->offset = fmt->width - len;
			assume: char *str = "123", len = 3, ft_printf("%5s", str);   
				=> fmt->width > len => fmt->offset = fmt->width - len;

		if (fmt->width > fmt->precision)
			fmt->offset = fmt->width - fmt->precision;
			assume: char *str = "123", len = 3, ft_printf("%5.2s", str);
				=> if (!fmt->dot || fmt->precision > len) (false)
				=> if (fmt->width > len) (true) => fmt->offset = 5 - 3 = 2;
				=> if (fmt->width > fmt->precision) (true) 
				=> adjust the offset => fmt->offset = 5 - 2 = 3;
	}
*/
