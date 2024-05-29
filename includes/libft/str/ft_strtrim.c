/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 00:35:54 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/21 19:34:34 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static int	ft_isset(char c, char const *set)
{
	while (*set)
	{
		if (*(unsigned char *)set == (unsigned char)c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1)
		return (NULL);
	else if (!set)
		return ((char *)s1);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_isset(s1[i], set))
		i++;
	while (s1[j] && ft_isset(s1[j], set) && j > 0)
		j--;
	len = j - i + 1;
	return (ft_substr(s1, i, len));
}

/*
	len = j - i + 1;
		+ 1 for the max and the min included and it's not for the '\0'.

	while (s1[j] && ft_isset(s1[j], set) && j > 0)
		The reason for j > 0 is this test case:
		s1[] = "          ", *set = " ";
		Once the j became 1 and s1[1] is indeed a set, the while loop decrement 
		the j to 0, if we had j >= 0, then the while loop will run again,
		causing the j to go in negative and since it's a size_t, 
		the j will overflow, j = 18446744073709551615.
*/
