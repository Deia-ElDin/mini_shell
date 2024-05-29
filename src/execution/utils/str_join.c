/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:16:11 by melshafi          #+#    #+#             */
/*   Updated: 2024/04/24 12:16:30 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*join_strs(char *str, char *buffer)
{
	char	*temp;

	temp = str;
	str = ft_strjoin(temp, buffer);
	return (free(temp), str);
}

void	free_2dchar(char **str)
{
	size_t	c;

	c = 0;
	while (str[c])
		free(str[c++]);
	free(str);
}
