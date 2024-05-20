/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:47:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/05/20 16:14:51 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
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
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		add_history(line);
		data.line = ft_strtrim(line, WHITESPACES);
		ft_free(&line, 'p');
		if (!data.line)
			exit_failure(&data);
		if (!lexer(&data))
			continue ;
		if (!parser(&data))
			continue ;
		execution(&data);
		data_reset(&data);
	}
	data_free(&data);
	return (data.exit_status);
}
