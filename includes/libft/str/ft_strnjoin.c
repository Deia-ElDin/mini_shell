/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:40:18 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/18 02:10:37 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static size_t	ft_total_len(int total, va_list args)
{
	size_t	total_len;

	total_len = 0;
	while (total--)
		total_len += ft_strlen(va_arg(args, const char *));
	return (total_len);
}

char	*ft_strnjoin(int total, ...)
{
	va_list		args;
	size_t		total_len;
	char		*tmp;
	char		*result;

	va_start(args, total);
	total_len = ft_total_len(total, args);
	if (!total_len)
		return (va_end(args), NULL);
	result = (char *)ft_calloc(total_len + 1, sizeof(char));
	if (!result)
		return (va_end(args), NULL);
	va_end(args);
	va_start(args, total);
	while (total--)
	{
		tmp = ft_strjoin(result, va_arg(args, const char *));
		if (!tmp)
			return (ft_free(&result, 'p'), va_end(args), NULL);
		ft_free(&result, 'p');
		result = tmp;
	}
	return (va_end(args), result);
}
