/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 02:05:19 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/28 21:03:50 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

static int	handle_count(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] && !ft_issep(s[i], c))
		{
			words++;
			while (s[i] && !ft_issep(s[i], c))
				i++;
		}
		else
			i++;
	}
	return (words);
}

static char	*handle_malloc(char	**split, char const *s, int first, int last)
{
	char	*word;
	size_t	i;

	word = ft_substr(s, first, last - first);
	if (!word)
	{
		i = 0;
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		return (NULL);
	}
	return (word);
}

static char	**handle_split(char	**split, char const *s, char c)
{
	int		i;
	int		index;
	int		st;

	i = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] && !ft_issep(s[i], c))
		{
			st = i;
			while (s[i] && !ft_issep(s[i], c))
				i++;
			split[index] = handle_malloc(split, s, st, i);
			if (!split[index])
			{
				free(split);
				return (NULL);
			}
			index++;
		}
		else
			i++;
	}
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	len;

	if (!s)
		return (NULL);
	len = handle_count(s, c) + 1;
	split = (char **)ft_calloc(len, sizeof(char *));
	if (!split)
		return (NULL);
	return (handle_split(split, s, c));
}
