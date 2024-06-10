/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:15:31 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/10 13:35:58 by melshafi         ###   ########.fr       */
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
