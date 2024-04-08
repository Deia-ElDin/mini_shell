/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:27:44 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/31 15:46:08 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len.h"

size_t	ft_ptrlen(void *ptr)
{
	size_t		len;
	uintptr_t	addr;

	len = 0;
	addr = (uintptr_t)ptr;
	while (addr && ++len)
		addr /= 16;
	return (len);
}

/*
	size_t
		Using size_t for the length of a pointer representation is a common 
		practice in C, because it is the appropriate type for representing 
		sizes and indices. It ensures consistency and portability across
		different platforms.

	uintptr_t
		Ensure portability and accuracy in representing pointers as integers.
		Represent a pointer as an integer without any loss of information.

	printf("addr = %lu\n", addr); lu as unsigned long
*/
