/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:40:47 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/02 18:10:31 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_echo(char *av[], int index, t_data *data)
{
	if (av[1] == NULL) {
		ft_putstr_fd("\n", data->pipes[index][1]);
		return(0);
	}
	else if (ft_strncmp(av[1], "-n", ft_strlen("-n")) == 0)	
		ft_print(av, 2, TRUE, index, data);
	else 
		ft_print(av, 1, FALSE, index, data);
	return (0);
	
}

void ft_print(char *av[], int i, int flag, int index, t_data *data)
{
	while (av[i])
	{
		ft_putstr_fd(av[i], data->pipes[index][1]);
		if (av[i + 1] != NULL)
			ft_putstr_fd(" ", data->pipes[index][1]);
		i++;
	}
	if (flag == FALSE)
		ft_putstr_fd("\n", data->pipes[index][1]);
}
