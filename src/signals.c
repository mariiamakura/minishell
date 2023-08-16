/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:01:16 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/16 14:22:29 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		g_last_exit = 130;
		exit (130);
	}
}

void	sig_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_last_exit = 130;
	}
}

void	sig_handler_heredoc(int signum)
{
	signal(SIGINT, SIG_IGN);
	if (signum == SIGINT)
	{
		g_last_exit = 130;
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (0 == ft_strlen(rl_line_buffer))
			rl_redisplay();
		g_last_exit = 130;
	}
}
