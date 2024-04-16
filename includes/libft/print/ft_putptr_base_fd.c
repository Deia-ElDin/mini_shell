/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 20:28:48 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/31 18:13:09 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_putptr_base_fd(void *ptr, int base, int fd)
{
	uintptr_t	addr;
	const char	*digits;

	addr = (uintptr_t) ptr;
	digits = "0123456789abcdef";
	if (addr / base)
		ft_putptr_base_fd((void *)(addr / base), base, fd);
	ft_putchar_fd(digits[addr % base], fd);
}
