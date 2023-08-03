/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:01:16 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/03 14:34:47 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void init_signals(void)
{
	g_global = malloc(sizeof(t_global));
	if (g_global == NULL)
	{
		ft_putstr_fd("global is not allocated", STDERR_FILENO);
		exit (-1);
	}
	g_global->c_kill_child = FALSE;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	signal(SIGCHLD, sig_handler);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		/*rl_on_new_line();
		//rl_replace_line("", 0);
		if (data->forked == FALSE)
		{
			rl_redisplay();
		} */
		g_global->c_kill_child = TRUE;
	}
}
