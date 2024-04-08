/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mal.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:46:22 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/29 00:17:02 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAL_H
# define MAL_H

# include "../libft.h"

void	*ft_calloc(size_t count, size_t size);
void	ft_free(void *address, char target);

#endif