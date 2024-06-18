#include "minishell.h"

static int	count_words(char const *s, char c)
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

static char	**split_words(char	**split, char const *s, char c)
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

char	**split_cmds(char const *s)
{
	char	**split;
	size_t	len;
	char	c;

	c = ' ';
	if (!s)
		return (NULL);
	len = count_words(s, c) + 1;
	split = (char **)ft_calloc(len, sizeof(char *));
	if (!split)
		return (NULL);
	return (split_words(split, s, c));
}