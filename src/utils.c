/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:57:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/11 14:48:35 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    print_env_list(t_env *lst)
{
    while (lst)
    {
        printf("key: %s\nvalue: %s\n\n", lst->key, lst->value);
        lst = lst->next;
    }
}