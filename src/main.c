/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:47:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/11 18:41:01 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>  

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		// exit(EXIT_SUCCESS);
	}
	else if (signo == SIGQUIT)
		printf("Quit: 3\n");
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	data.env = env;
	data.av = av;
	data.exit_status = 0;
	data.env_list = NULL;
	data.env_list = env_to_list(env);
	// print_env_list(data.env_list);
	data.env = list_to_env(data.env_list);
	data.path = get_path(data.env_list);
	data.history = NULL;
	data.history = init_history(data.history);
	data.history->current = data.history->head;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		data.line = readline("minishell$ ");
		if (data.line == NULL)
			break ;
		printf("line: %s\n", data.line);
		// if (ft_strlen(data.line) > 0)
		// 	add_history(data.line, data.history);
		// data.tokens = lexer(data.line);
		// data.ast = parser(data.tokens);
		// exec_ast(data.ast, &data);
		// free_tokens(data.tokens);
		// free_ast(data.ast);
		// free(data.line);
	}
	// free_history(data.history);
	// free_env_list(data.env_list);
	// free_path(data.path);
	// free_env(data.env);
	// return (data.exit_status);
}


/*
	dehamad@lab1r3s1 mini_shell % kill -TERM 7200
	dehamad@lab1r3s1 mini_shell % kill -STOP 7200
	dehamad@lab1r3s1 mini_shell % kill -CONT  7200
*/

/*
	ps -f 1
	0     1     0   0 Sat06AM ??        22:35.16 /sbin/launchd
	launchd: service management framework used by macOS
	service: is anything running in the background
	When you turn on your Mac, launchd is one of the first 
	things launched, after the kernel
*/
