/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:45:33 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/03 13:18:05 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s) + 1;
	dup = (char *)ft_calloc(slen, sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, slen);
	return (dup);
}
