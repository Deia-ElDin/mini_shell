/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:31:19 by dehamad           #+#    #+#             */
/*   Updated: 2024/03/17 21:28:40 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;

	if (src && !dstsize)
		return (ft_strlen(src));
	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	if (dstsize <= dlen)
		return (dstsize + slen);
	ft_strlcpy(dst + dlen, src, dstsize - dlen);
	return (dlen + slen);
}
