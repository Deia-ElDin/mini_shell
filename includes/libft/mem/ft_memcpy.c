/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 14:34:15 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 12:59:29 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	cpy;

	if (!dst && !src)
		return (NULL);
	cpy = n;
	while (n--)
		*(char *)dst++ = *(char *)src++;
	return (dst - cpy);
}
