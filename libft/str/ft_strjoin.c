/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:55:24 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/01 13:32:24 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1 || !*s1)
		return (ft_strdup(s2));
	else if (!s2 || !*s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, len1 + 1);
	ft_strlcat(join, s2, len1 + len2 + 1);
	return (join);
}
