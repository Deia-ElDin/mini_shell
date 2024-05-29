/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:00:21 by dehamad           #+#    #+#             */
/*   Updated: 2024/03/21 00:43:33 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUM_H
# define NUM_H

# include "../libft.h"

typedef struct s_atoi
{
	long	nbr;
	bool	error;
}	t_atoi;

t_atoi	ft_atoi(const char *str);
char	*ft_itoa(int n);

#endif