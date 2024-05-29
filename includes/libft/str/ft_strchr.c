/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:16:16 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 12:35:21 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s && *(unsigned char *)s != (unsigned char)c)
		s++;
	if (*(unsigned char *)s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

/*
	When you cast *s to (unsigned char), you are ensuring that the comparison 
	is done using an unsigned type. This is especially relevant when dealing 
	with character values greater than 127 (which may have different 
	representations if treated as signed or unsigned).

	n essence, the explicit cast to (unsigned char) ensures consistent 
	and expected behavior across different systems, regardless of the 
	default signedness of char. It's a good practice to make your code 
	more robust and less dependent on implementation details.
*/
