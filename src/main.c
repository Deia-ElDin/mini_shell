/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:47:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/20 19:28:51 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	disable_ctrl_c_echo(void)
{
	struct termios	new_term;

	new_term = (struct termios){0};
	tcgetattr(STDIN_FILENO, &new_term);
	new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*line;

	(void)ac;
	(void)av;
	line = NULL;
	data_init(&data, env);
	disable_ctrl_c_echo();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		add_history(line);
		data.line = ft_strtrim(line, WHITESPACES);
		ft_free(&line, 'p');
		if (!data.line)
			exit_shell(&data);
		if (lexer(&data) && parser(&data))
		{
			// print_ast(data.ast);
			prepare_heredocs(data.ast, &data);
			execution(&data);
		}
		data_reset(&data);
	}
	data_free(&data);
	return (data.exit_status);
}
