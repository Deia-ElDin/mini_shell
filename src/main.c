/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:47:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/16 19:50:04 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	signal_handler(int signo)
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
	char	*line;

	(void)ac;
	(void)av;
	line = NULL;
	init_data(&data, env);
	// print_env_list(data.env_list);
	// print_path(data.path);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		data.line = ft_strtrim(line, WHITESPACES); // check if \n only
		if (ft_strlen(data.line) > 0)
			add_history(line);
		free(line);
		if (!data.line)
			exit_failure(&data);
		data.tokens = lexer(&data);
		print_tokens(data.tokens);
		// data.ast = parser(&data);
		// print_ast(data.ast);
		// exec_ast(data.ast, &data);
		free_tokens(data.tokens);
		free_ast(data.ast);
		free(data.line);
	}
	free_data(&data);
	return (data.exit_status);
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
