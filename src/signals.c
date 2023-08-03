/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:01:16 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/03 22:56:19 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void init_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler_parent);
	//signal(SIGCHLD, sig_handler);
}

void	sig_handler_child(int signum)
{
	if (signum == SIGINT)
	{
		last_exit_global = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sig_handler_parent(int signum)
{
	if (signum == SIGINT)
	{
		last_exit_global = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}