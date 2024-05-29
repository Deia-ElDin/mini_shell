/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:44:45 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/03 12:37:43 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	slen;

	if (!src || !dst)
		return (0);
	slen = ft_strlen(src);
	if (dstsize == 0)
		return (slen);
	while (*src && (dstsize-- > 1))
		*dst++ = *src++;
	*dst = '\0';
	return (slen);
}

/*
	while (*src && (dstsize-- > 1))
		The purpose of this condition (*src) to check that dereferencing the src
		doesn't point to null terminator.

	assume:
		1) const char *ptr1 = NULL;
			-> this is the best practice, 
			you create a ptr and initilize it with null.
		2) const char *ptr2;
			*ptr2 = '\0';
			-> This is wrong and might result in undefined behaviour,
			because we didn't initilize the ptr and we are dereferencing
			what we didn't initilize and trying to set that to null.
			-> This what we will get if our dst is not initilized outside the fn,
			and we didn't check if (!*src).
*/
