/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:15:37 by melshafi          #+#    #+#             */
/*   Updated: 2024/05/20 19:21:23 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	handle_pipe_cmd(t_data *data)
// {

// }

int	pipe_cmd(t_ast *ast, t_data *data)
{
	data->ast = ast->left;
	if (ast->left->left && ast->left->right)
		execution(data);
	data->ast = ast->right;
	if (ast->right->left && ast->right->right)
		execution(data);
	return (0);
}

/*

Handle pipe commands manually in handle_pipe_cmd instead of simple_cmd,
Follow this heirarchy and order of pipe closures and dups:

case PIPE:
    pcmd = (struct pipecmd*)cmd;
    if(pipe(p) < 0)
      panic("pipe");
    if(fork1() == 0){
      close(1);
      dup(p[1]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->left);
    }
    if(fork1() == 0){
      close(0);
      dup(p[0]);
      close(p[0]);
      close(p[1]);
      runcmd(pcmd->right);
    }
    close(p[0]);
    close(p[1]);
    wait();
    wait();
    break;


SOURCE: https://github.com/mit-pdos/xv6-public/blob/master/sh.c
@line:100

*/
