/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:14:24 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/28 21:20:40 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mal.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && count > (UINT_MAX / size))
		return (NULL);
	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}

/*
	The formula size * count ensures that you allocate enough space 
	to store count elements, and each element is size bytes long. 
	This is the standard approach to calculate the total size for memory
	allocation in functions like calloc or malloc where you need to 
	allocate memory for an array of elements.
*/
