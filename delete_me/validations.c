/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 04:44:36 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/21 19:01:44 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"

/**
 * The purpose of this function is to scan the line before and after the target
 * the scanning of the content depends on the direction (+ or -)
 * if +, the scanning will be from the target to the end of the line
 * if -, the scanning will be from the target to the beginning of the line
 * if it found any char which is not a whitespace then it's a valid case
 * we don't loop over the whole string, once we find a valid char we break
 * if we found a valid char we increment the flag is_char 
 * then at the end we check if !is_char we print err depending on the target
*/

// static bool	scan_context(const char *line, int i, char target, char direction)
// {
// 	int		is_char;

// 	is_char = 0;
// 	if (i < 0 && target == '|')
// 		return (syntax_error("|"), false);
// 	while (line[i])
// 	{
// 		if (line[i] == target)
// 			break ;
// 		else if (!ft_isspace(*line) && ++is_char)
// 			break ;
// 		if (direction == '+')
// 			i++;
// 		else
// 			i--;
// 		if (i < 0 && target == '|')
// 			return (syntax_error("|"), false);
// 	}
// 	if (!is_char && target == '|')
// 		return (syntax_error("|"), false);
// 	else if (!is_char && ft_isredirect(target))
// 		return (syntax_error("newline"), false);
// 	return (true);
// }

// /**
//  * The purpose of this function is to validate the quotes
//  * we loop over the line and check if there is any quotes
//  * if !quotes and we found a quote we set the quotes to the current quote
//  * if quotes and we found the same quote we set the quotes back to 0
//  * if quotes is not 0 (we didn't find a match quotes) then it's an error
// */

// static bool	validate_quotes(t_data *data)
// {
// 	const char	*line;
// 	char		quotes;
// 	int			i;

// 	line = data->line;
// 	quotes = '\0';
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (ft_isquote(line[i]))
// 		{
// 			if (!quotes)
// 				quotes = line[i];
// 			else if (quotes == line[i])
// 				quotes = '\0';
// 		}
// 		i++;
// 	}
// 	if (quotes)
// 		return (syntax_error(&quotes), false);
// 	return (true);
// }

/**
 * The purpose of this function is to validate the pipe
 * we loop over the line and check if there is any pipe
 * if we found a pipe we scan the context before and after the pipe
*/

// static bool	validate_pipe(t_data *data)
// {
// 	const char	*line;
// 	int			i;

// 	line = data->line;
// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '|')
// 			return (scan_context(line, i - 1, '|', '-')
// 				&& scan_context(line, i + 1, '|', '+'));
// 		i++;
// 	}
// 	return (true);
// }

/**
 * The purpose of this function is to validate the redirection
 * we loop over the line and check if there is any redirection
 * if we found a redirection we scan the context only after the redirection
*/

// static bool	validate_redirection(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->line[i])
// 	{
// 		if (data->line[i] == '>' || data->line[i] == '<')
// 		{			
// 			if (data->line[i] == data->line[i + 1])
// 				i++;
// 			return (scan_context(data->line, i + 1, data->line[i], '+'));
// 		}
// 		i++;
// 	}
// 	return (true);
// }

/**
 * The purpose of this function is to validate the line
 * we check if the line is not null for safety purposes
 * then we call the validation functions
*/

// bool	validations(t_data *data)
// {
// 	if (!data->line)
// 		return (false);
// 	return (validate_quotes(data)
// 		&& validate_pipe(data)
// 		&& validate_redirection(data));
// }
