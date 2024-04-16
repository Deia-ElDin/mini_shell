/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:49:25 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 12:59:22 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
	}
	return (NULL);
}

/*
	In the case of ft_memchr, you are searching for a byte 
	within a block of memory (n bytes).
	Casting s to unsigned char * allows you to treat the memory 
	as an array of unsigned characters, 
	and it's common to do so when working with raw memory.

	On the other hand, ft_strchr is designed to find the first occurrence
	of a character (c) in a null-terminated string (s). In C, strings are 
	represented as arrays of characters, and it is guaranteed that each 
	character in a string is a valid value in the range of unsigned char
	(0 to 255). Therefore, casting s to unsigned char * in ft_strchr 
	might not be necessary.
*/
