/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 06:44:37 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/01 13:33:07 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

char	*ft_itoa(int n)
{
	char	*itoa;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	len = ft_intlen(n);
	itoa = (char *)ft_calloc((ft_intlen(n) + 1), sizeof(char));
	if (!itoa)
		return (NULL);
	itoa[len] = '\0';
	if (n < 0)
	{
		itoa[0] = '-';
		n *= -1;
	}
	while (n)
	{
		itoa[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (itoa);
}
