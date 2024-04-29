/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:47:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/04/29 22:55:16 by dehamad          ###   ########.fr       */
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
	data_init(&data, env);
	// printf("size = %d\n", env_lstsize(&data));
	// print_env_array(data.env);
	// print_env_list(data.env_list);
	// print_path(data.path);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			data.line = ft_strtrim(line, WHITESPACES);
			ft_free(&line, 'p');
			if (!data.line)
				exit_failure(&data);
			if (!lexer(&data))
				continue ;
			parser(&data);
			// exec_ast(data.ast, &data);
			data_reset(&data);
		}
	}
	data_free(&data);
	return (data.exit_status);
}

