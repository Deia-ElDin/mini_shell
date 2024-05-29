/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 09:19:59 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 15:21:38 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strcdup(const char *s, int c)
{
	char	*dup;
	size_t	len;

	len = 0;
	if (!s)
		return (NULL);
	if (ft_strchr(s, c))
		len = (size_t)(ft_strchr(s, c) - s);
	else
		len = ft_strlen(s);
	if (!len)
		return (NULL);
	dup = ft_calloc(len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}
