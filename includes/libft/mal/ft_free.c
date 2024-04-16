/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:04:05 by dehamad           #+#    #+#             */
/*   Updated: 2024/03/17 22:15:35 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mal.h"

static void	free_ptr(void **ptr)
{
	if (!ptr || !(*ptr))
		return ;
	free(*ptr);
	*ptr = NULL;
}

static void	free_arr(void ***arr)
{
	void	**cpy;

	if (!arr || !(*arr))
		return ;
	cpy = *arr;
	while (*cpy)
	{
		free_ptr(cpy);
		cpy++;
	}
	free(*arr);
	*arr = NULL;
}

void	ft_free(void *address, char target)
{
	if (!address || !target)
		return ;
	if (target == 'p')
		free_ptr((void **)address);
	else if (target == 'a')
		free_arr((void ***)address);
	else
		return ;
}

/*
	static void	free_ptr(void **ptr)
	{
		if (!ptr || !(*ptr))
			we are checking if the ptr it self is NULL 
			or the value it points to is NULL, \0
	}
	
	arr: Pointer to a pointer to a pointer to void (e.g., void ***).
	*arr: Dereferencing once gives you a 
		pointer to a pointer to void (e.g., void **).
	cpy: Assigned the dereferenced value of *arr, 
		so cpy is also a pointer to a pointer to void (e.g., void **).

	if we used the *arr directly instead of cpy,
	at the time we free(*arr) we will be freeing the NULL.
*/
