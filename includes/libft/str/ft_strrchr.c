/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 20:50:54 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 12:35:42 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = NULL;
	while (*s)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			ret = (char *)s;
		s++;
	}
	if (*(unsigned char *)s == (unsigned char)c)
		ret = (char *)s;
	return (ret);
}
