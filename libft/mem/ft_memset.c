/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:43:54 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 12:59:33 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	cpy;

	cpy = len;
	while (len--)
		*(char *)b++ = (unsigned char)c;
	return (b - cpy);
}
