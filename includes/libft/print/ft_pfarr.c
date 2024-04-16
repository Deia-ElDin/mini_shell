/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfarr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:02:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/03/18 05:30:15 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_pfarr(t_fmt *fmt)
{
	char	**arr;
	char	*str;
	size_t	len;
	int		index;

	arr = va_arg(fmt->args, char **);
	index = 0;
	while (arr[index])
	{
		str = arr[index];
		len = ft_strlen(str);
		fmt->len += ft_strlen(arr[index]);
		ft_putstr_fd(arr[index++], fmt->fd);
		if (str[len - 1] != '\n')
			ft_putchar_fd('\n', fmt->fd);
	}
}
