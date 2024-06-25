/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:58:31 by melshafi          #+#    #+#             */
/*   Updated: 2024/06/25 16:58:34 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		token_type(char *token);
static t_token	*token_values(t_data *data, char *value, int index);
static t_token	*token_new(t_data *data, int start, int len);
void			token_add(t_data *data, t_token **head, int start, int len);

/// @brief Used to get the type of the token
/// @param token The token to be checked
/// @return The type of the token
static int	token_type(char *token)
{
	if (*token == '\'')
		return (TOKEN_SINGLE_QUOTE);
	if (*token == '\"')
		return (TOKEN_DOUBLE_QUOTE);
	if (!ft_strcmp(token, "&&"))
		return (TOKEN_AND);
	if (!ft_strcmp(token, "||"))
		return (TOKEN_OR);
	if (!ft_strcmp(token, "<<"))
		return (TOKEN_HEREDOC);
	if (!ft_strcmp(token, ">>"))
		return (TOKEN_APPEND);
	if (!ft_strcmp(token, "<"))
		return (TOKEN_REDIR_IN);
	if (!ft_strcmp(token, ">"))
		return (TOKEN_REDIR_OUT);
	if (!ft_strcmp(token, "|"))
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

/// @brief Used to set the token struct values
/// @param data The main struct
/// @param value The value of the token
/// @param index The index at which the token ends (sum + len)
/// @return The new token values
static t_token	*token_values(t_data *data, char *value, int index)
{
	t_token	*token;
	char	*dollar_sign;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (data_status(data, 1), NULL);
	token->type = token_type(value);
	dollar_sign = ft_strchr(value, '$');
	if (dollar_sign && *(dollar_sign + 1) != '"' && *(dollar_sign + 1) != ' '
		&& token->type != TOKEN_SINGLE_QUOTE && ft_strlen(value) > 1)
		token->value = env_expansion(data, value);
	else
		token->value = ft_strtrim(value, WHITESPACES);
	if (!token->value)
		return (free(token), NULL);
	if (data->line[index] == ' ')
		token->is_space = true;
	else
		token->is_space = false;
	token->is_parsed = false;
	token->prev = NULL;
	token->next = NULL;
	return (token);
}

/**
 * The purpose of this function is to set the token struct values
 * we check if the value has a '$' and the token is not a single quote
 * which means it's either a DOUBLE_QUOTE or CMD
 * which means it's either a DOUBLE_QUOTE or CMD
 * we set the value of the token by expanding the env variables
 * else we trim the value to remove the whitespaces
 * we check if the next char is a space or not, for example
 * echo "hi""there" => hithere, echo "hi" "there" => hi there
 * so we need to find out if there's a space between them or not
 * once we clean the token_lst we will either add a space or not
*/

/// @brief Used to create a new token
/// @param data The main struct
/// @param start The head of the token linked list
/// @param len The starting index of the token at the line
/// @return The new token
static t_token	*token_new(t_data *data, int start, int len)
{
	char	*value;
	t_token	*new;

	if (!data->line || !len)
		return (NULL);
	value = ft_substr(data->line, start, (size_t)len);
	if (!value)
		return (data_status(data, 1), NULL);
	if (ft_isempty_str(value))
		return (ft_free(&value, 'p'), NULL);
	new = token_values(data, value, start + len);
	ft_free(&value, 'p');
	if (!new)
		return (NULL);
	return (new);
}

/**
 * The purpose of this function is to create a new token
 * if the line is empty or the len is 0 we return NULL (protections)
 * we get the value of the token by using ft_substr
 * we make sure it's not an empty string ("   "), ("")
 * if it's an empty string, we free the value and return NULL
 * then we use token_values to fill the token struct values
*/

/// @brief Used to add a token to the linked list
/// @param data The main struct
/// @param head The head of the token linked list
/// @param start The starting index of the token at the line
/// @param len The length of the token (how many char it has)
void	token_add(t_data *data, t_token **head, int start, int len)
{
	t_token	*token;
	t_token	*tmp;

	token = token_new(data, start, len);
	if (!token)
		return ;
	tmp = *head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!*head)
	{
		token->index = 0;
		*head = token;
	}
	else
	{
		token->index = tmp->index + 1;
		tmp->next = token;
		token->prev = tmp;
	}
}

/**
 * The purpose of this function is to add a token to the linked list
 * we create a new token
 * we loop over the linked list to get the last token
 * if the head is NULL we set the head to the token
 * else we set the last token next to the new token
*/
