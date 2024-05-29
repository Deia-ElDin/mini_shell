/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mal.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:46:22 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/13 16:56:33 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAL_H
# define MAL_H

# include "../libft.h"

void	*ft_calloc(size_t count, size_t size);
void	ft_free(void *address, char target);
void	ft_bzero(void *s, size_t n);

#endif