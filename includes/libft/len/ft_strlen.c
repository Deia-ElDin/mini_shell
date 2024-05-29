/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:14:22 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/03 12:43:44 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (*s && ++len)
		s++;
	return (len);
}
