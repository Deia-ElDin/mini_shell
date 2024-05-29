/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:41:50 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/28 22:50:57 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEN_H
# define LEN_H

# include "../libft.h"

size_t	ft_intlen(int n);
size_t	ft_strlen(const char *s);
size_t	ft_ptrlen(void *ptr);
size_t	ft_uintlen_base(unsigned int nbr, int base);

#endif