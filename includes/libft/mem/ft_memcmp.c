/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:51:51 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 12:59:26 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (i < n - 1 && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

/*
	`\200' is greater than `\0'
		1) the \ indicates the start of an escape sequence.
		2) the 2 is the first octal digit.
		3) the 00 together are the next two octal digits.
	
	\200 => decimal = 2 * 8^2 + 0 * 8^1 + 0 * 8^0 = 128.
	128 => hexa => 
		128 / 16  = 8 and remainder = 0. 
		8 / 16 = 0 and remainder = 8.
		0x80;

		// if (!s1 && !s2)
	// 	return (0);
*/
