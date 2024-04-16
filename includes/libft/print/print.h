/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:06:12 by dehamad           #+#    #+#             */
/*   Updated: 2024/03/28 13:59:35 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "../libft.h"

# define SPECIFIERS "cspdiuxXal%"

typedef struct s_fmt
{
	int		len;
	int		width;
	int		offset;
	int		pad;
	int		precision;
	int		dot;
	int		plus;
	int		minus;
	int		zero;
	int		hashtag;
	int		upper;
	int		space;
	int		fd;
	va_list	args;
}	t_fmt;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putlchar_fd(size_t len, char c, int fd);
void	ft_putlstr_fd(char *s, size_t len, int fd);
void	ft_putptr_base_fd(void *ptr, int base, int fd);
void	ft_putnbr_base_fd(unsigned int nbr, int base, int uppercase, int fd);

// ft_printf
int		ft_printf(int fd, const char *format, ...);
void	ft_pfchar(t_fmt *fmt, char c);
void	ft_pfstr(t_fmt *fmt);
void	ft_pfptr(t_fmt *fmt);
void	ft_pfint(t_fmt *fmt);
void	ft_pfunit(t_fmt *fmt, int base);
void	ft_pfarr(t_fmt *fmt);
void	ft_reset_fmt(t_fmt *fmt, char type);
void	ft_pfputnbr_base(t_fmt *fmt, long long nbr, int base);

#endif
