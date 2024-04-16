/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:03:01 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 12:59:31 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = dst;
	s = src;
	if (dst > src)
	{
		d += len;
		s += len;
		while (len--)
			*(--d) = *(--s);
	}
	else if (dst < src)
	{
		while (len--)
			*(d++) = *(s++);
	}
	return (dst);
}
