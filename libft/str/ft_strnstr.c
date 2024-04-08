/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 11:04:07 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 12:35:40 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;

	if (!*needle)
		return ((char *)haystack);
	if (!haystack && !len)
		return (NULL);
	nlen = ft_strlen(needle);
	while (*haystack && len >= nlen)
	{
		if (!ft_strncmp(haystack, needle, nlen))
			return ((char *)(haystack));
		len--;
		haystack++;
	}
	return (NULL);
}
