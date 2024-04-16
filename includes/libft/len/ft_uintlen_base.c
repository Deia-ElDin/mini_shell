/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintlen_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 22:15:49 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/28 22:50:23 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "len.h"

size_t	ft_uintlen_base(unsigned int nbr, int base)
{
	size_t	len;

	len = 0;
	if (!nbr)
		len++;
	while (nbr && ++len)
		nbr /= base;
	return (len);
}
