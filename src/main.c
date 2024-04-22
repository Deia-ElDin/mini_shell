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
	// printf("size = %d\n", env_size(&data));
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
			{
				free_data(&data);
				continue ;
			}
			// print_tokens(data.tokens);
			data.ast = parser(&data);
			print_ast(data.ast);
			// exec_ast(data.ast, &data);
			token_clear(&data);
			// free_ast(data.ast);
			ft_free(&data.line, 'p');
		}
	}
	free_data(&data);
	return (data.exit_status);
}

