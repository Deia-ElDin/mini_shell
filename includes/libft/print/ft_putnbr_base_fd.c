/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 11:43:10 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/26 03:56:45 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_putnbr_base_fd(unsigned int nbr, int base, int uppercase, int fd)
{
	int		sign;
	char	*digits;

	sign = 1;
	digits = "0123456789abcdef";
	if (uppercase)
		digits = "0123456789ABCDEF";
	if (nbr / base)
		ft_putnbr_base_fd(sign * (nbr / base), base, uppercase, fd);
	ft_putchar_fd(digits[sign * (nbr % base)], 1);
}
