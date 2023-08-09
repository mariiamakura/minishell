/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:01:16 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/09 15:13:05 by mparasku         ###   ########.fr       */
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
