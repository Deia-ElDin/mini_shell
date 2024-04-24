/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:47:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/22 17:57:03 by melshafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);

	// t_ast left1 = {
	// 	.end_flag = 1,
	// 	.type = NODE_CMD,
	// 	.cmd = "/bin/pwd",
	// 	.args = NULL,
	// 	.file = NULL,
	// 	.left = NULL,
	// 	.right = NULL
	// };
	// t_ast right1 = {
	// 	.end_flag = 0,
	// 	.type = NODE_CMD,
	// 	.cmd = NULL,
	// 	.args = (char *[]){NULL},
	// 	.file = NULL,
	// 	.left = NULL,
	// 	.right = NULL
	// };
	// t_ast head1 = {
	// 	.end_flag = 1,
	// 	.type = NODE_CMD,
	// 	.cmd = NULL,
	// 	.args = NULL,
	// 	.file = NULL,
	// 	.left = &left1,
	// 	.right = &right1
	// };

	t_ast left2 = {
		.end_flag = 1,
		.type = NODE_CMD,
		.cmd = "/usr/bin/ls",
		.args = NULL,
		.file = NULL,
		.left = NULL,
		.right = NULL
	};
	t_ast right2 = {
		.end_flag = 0,
		.type = NODE_CMD,
		.cmd = NULL,
		.args = (char *[]){NULL},
		.file = NULL,
		.left = NULL,
		.right = NULL
	};
	t_ast head2 = {
		.end_flag = 1,
		.type = NODE_CMD,
		.cmd = NULL,
		.args = NULL,
		.file = NULL,
		.left = &left2,
		.right = &right2
	};

	// t_ast head = {
	// 	.end_flag = 1,
	// 	.type = NODE_PIPE,
	// 	.cmd = NULL,
	// 	.args = NULL,
	// 	.file = NULL,
	// 	.left = &head1,
	// 	.right = &head2
	// };
	exec_ast(&head2, &data);
	// token_clear(&data);
	// free_data(&data);
	return (data.exit_status);
}

