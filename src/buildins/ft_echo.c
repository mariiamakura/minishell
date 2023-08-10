/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:40:47 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/10 15:27:06 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_echo(char *av[], t_data *data, int index)
{
	if (av[1] == NULL) {
		ft_putstr_fd("\n", data->pipes[index][1]);
	}
	else if (ft_strncmp(av[1], "-n", ft_strlen(av[1])) == 0 
			&& ft_strlen(av[1]) == ft_strlen("-n"))
		ft_print(av, 2, TRUE, index, data);
	else 
		ft_print(av, 1, FALSE, index, data);
	last_exit_global = 0;
	return (last_exit_global);
	
}

void ft_print(char *av[], int i, int flag, int index, t_data *data)
{
	char *home_dir;

	home_dir = ft_get_env_value(data, "HOME");
	while (av[i])
	{
		if ((ft_strncmp(av[i], "~", ft_strlen(av[i]))) == 0 && ft_strlen(av[i]) == ft_strlen("~")) //do ex cases Emilie sent pdf 
		{
			ft_putstr_fd(home_dir, data->pipes[index][1]);
		}
		else 
		{
			ft_putstr_fd(av[i], data->pipes[index][1]);
		}
		if (av[i + 1] != NULL)
			ft_putstr_fd(" ", data->pipes[index][1]);
		i++;
	}
	if (flag == FALSE)
		ft_putstr_fd("\n", data->pipes[index][1]);
	free(home_dir);
}

//check echo
