/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 02:44:39 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/17 17:31:11 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	skip_spaces(const char *line, int *i)
// {
// 	printf("skip_spaces line[%d]: %c\n", *i, line[*i]);
// 	if (line[*i] == '\0')
// 		return ;
// 	if (!ft_isspace(line[*i]))
// 		(*i)++;
// 	while (line[*i] && ft_isspace(line[*i]))
// 		(*i)++;
// }

// void	skip_quotes(const char *line, int *i)
// {
// 	char	quote;

// 	if (line[*i] == '\0')
// 		return ;
// 	if (!ft_isquote(line[*i]))
// 		(*i)++;
// 	quote = line[*i];
// 	(*i)++;
// 	while (line[*i] && line[*i] != quote)
// 		(*i)++;
// }
