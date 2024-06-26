/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 02:47:52 by dehamad           #+#    #+#             */
/*   Updated: 2024/06/26 11:03:46 by melshafi         ###   ########.fr       */
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
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	enter_mini(t_data *data)
{
	if (!data->line)
		exit_shell(data);
	if (lexer(data) && parser(data))
	{
		prep_heredocs(data->ast, data);
		open_all_redirs(data);
		execution(data);
		wait_on_pids(data);
	}
	data_reset(data);
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
		if (!*line && (free(line), 1))
			continue ;
		data.line = ft_strtrim(line, WHITESPACES);
		ft_free(&line, 'p');
		enter_mini(&data);
	}
	data_free(&data);
	return (data.exit_status);
}
