/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:47:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/03 11:03:25 by melshafi         ###   ########.fr       */
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
		prepare_heredocs(data.ast, &data);
		// print_ast(data.ast);
		execution(&data);
		data_reset(&data);
	}
	data_free(&data);
	return (data.exit_status);
}

/*
Rework redirection node types, create structs for each redirection type, additionally
rework the hardcoded implementation of checking for redirection in parse_cmd file,
it must instead look through all the next redirection and take the last as the redirection
to be applied, it must also work with different types

Ex: cat < 1 < 2 < 3 > 3 > 2 > 1
this should be equivilant to cat < 3 > 1
the redir in doesnt create any files, but redir out will create files 3 and 2 before outputting
to the final file 1. Additionally any failure in opening files should exit that commands exec
with the appropriate error message and exit status code.
*/
