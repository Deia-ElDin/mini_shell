/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:15:31 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 14:09:16 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

/*
	we don't need a while loop here to write the whole string.

	write(fd, s, ft_strlen(s));
		basically it does write (ft_strlen(s)) bytes,
		from the memory location pointed to by the ptr s. Excluding NULL.
		to the fd file.
*/
