/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:15:11 by dehamad           #+#    #+#             */
/*   Updated: 2024/03/28 13:59:46 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

static void	init_reset_fmt(t_fmt *fmt)
{
	fmt->width = 0;
	fmt->offset = 0;
	fmt->pad = 0;
	fmt->precision = 0;
	fmt->dot = 0;
	fmt->plus = 0;
	fmt->minus = 0;
	fmt->zero = 0;
	fmt->hashtag = 0;
	fmt->upper = 0;
	fmt->space = 0;
}

static void	set_fmt(t_fmt *fmt, char c)
{
	if (ft_isdigit(c))
	{
		if (fmt->dot)
			fmt->precision = ft_toint(fmt->precision, c);
		else
		{
			if (!fmt->width && c == '0')
				++fmt->zero;
			else
				fmt->width = ft_toint(fmt->width, c);
		}
	}
	else if (c == '.')
		++fmt->dot;
	else if (c == '-')
		++fmt->minus;
	else if (c == '+')
		++fmt->plus;
	else if (c == '#')
		++fmt->hashtag;
	else if (c == ' ')
		++fmt->space;
}

static char	*handle_print(char *format, t_fmt *fmt)
{
	while (!ft_strchr(SPECIFIERS, *format))
		set_fmt(fmt, *format++);
	if (*format == '%')
		ft_pfchar(fmt, '%');
	else if (*format == 'c')
		ft_pfchar(fmt, va_arg(fmt->args, int));
	else if (*format == 's')
		ft_pfstr(fmt);
	else if (*format == 'p')
		ft_pfptr(fmt);
	else if (*format == 'd' || *format == 'i')
		ft_pfint(fmt);
	else if (*format == 'u')
		ft_pfunit(fmt, 10);
	else if (*format == 'x')
		ft_pfunit(fmt, 16);
	else if (*format == 'X' && ++fmt->upper)
		ft_pfunit(fmt, 16);
	else if (*format == 'a')
		ft_pfarr(fmt);
	init_reset_fmt(fmt);
	return (++format);
}

int	ft_printf(int fd, const char *format, ...)
{
	int		count;
	t_fmt	fmt;

	if (!format)
		return (0);
	count = 0;
	fmt.len = 0;
	fmt.fd = fd;
	init_reset_fmt(&fmt);
	va_start(fmt.args, format);
	if (fd == 2)
		ft_putstr_fd("\033[1;31m", 2);
	while (*format)
	{
		if (*format == '%' && format++)
			format = handle_print((char *)format, &fmt);
		else if (++count)
			ft_putchar_fd(*format++, fd);
	}
	if (fd == 2)
		ft_putstr_fd("\033[0m", 2);
	count += fmt.len;
	va_end(fmt.args);
	return (count);
}

/*
	In C, a function with a variable number of arguments,
		is typically declared using an ellipsis (...) in the argument list.
		for example: ft_printf(const char *format, ...)
		Now, if you want to access the variable arguments within the function,
		you use the va_list type to hold information about those arguments.
		Declaring va_list variable:
			va_list args;

	va_list: 
		It is a type to hold information about the variable arguments. 
		It is usually a pointer type.

	va_start(va_list ap, last_arg): 
		It's a macro to initializes the va_list variable,
			to point to the first unnamed argument in the function.
		This macro must be called first before using va_arg().

	va_arg(va_list ap, type): 
		This macro retrieves the next argument in the variable argument list.
		The type parameter is the type of the next argument expected. 
		It returns the value of the argument,
			and advances the va_list to the next argument.

	va_end(va_list ap): 
		This macro cleans up the va_list,
			after variable arguments have been processed.
		It must be called before the function exits.

	int	ft_printf(const char *format, ...)
	{
		- the count: is the total number of whatever we did print.
		- init_reset_fmt(&fmt): initilaize our fmt to all zeros.
		- va_start(fmt.args, format): set the args inside our fmt.
		- while 
		{
			if (*format == '%' && format++)
				if we found a match we increment the format,
				so once we access the handle print we are on the next letter.
				
				format = handle_print((char *)format, &fmt);
					handle_print returns the char* it did check last,
					so we continuo our looping from that char
			else
				it's just a normal text, so count++; and print
		}
		count += our fmt->len (based on the pad, offset & len).
	}
*/
