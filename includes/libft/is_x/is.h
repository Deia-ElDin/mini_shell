/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 12:05:42 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/20 16:20:59 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_H
# define IS_H

# include "../libft.h"

int	ft_isalpha(int c);
int	ft_isdigit(int c);
int	ft_isalnum(int c);
int	ft_isascii(int c);
int	ft_isprint(int c);
int	ft_issep(char s, char c);
int	ft_isspace(int c);
int	ft_issign(int c);
int	ft_isdifferent_sign(int num1, int num2);
int	ft_isempty_str(char *str);
int	ft_ispipe(int c);
int	ft_isredirect(char *str);
int	ft_isdoubles(char *str);
int	ft_isquote(int c);

#endif