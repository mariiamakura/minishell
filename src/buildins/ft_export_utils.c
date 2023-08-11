/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:25:28 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/11 17:05:25 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	var_name_error_new(char **var, int arg_num)
{
	int	j;
	int	ret;

	j = 0;
	ret = 0;
	while (j < arg_num - 1)
	{
		if (var[j] == NULL)
			ret = ft_print_error_buildins("not a valid identidier", "");
		else if (var[j][0] != '\0')
		{
			if (!(var[j][0] >= 'a' && var[j][0] <= 'z') 
				&& !(var[j][0] >= 'A' && var[j][0] <= 'Z')
				&& var[j][0] != '_')
			{
				ret = ft_print_error_buildins("not an identifier: ", var[j]);
				free (var[j]);
				var[j] = NULL;
			}
		}
		j++;
	}
	return (ret);
}

int	ft_is_var_in_env(t_data *data, char *var_name)
{
	int		i;
	int		flag;
	int		size;
	char	*data_env;

	i = 0;
	flag = FALSE;
	size = 0;
	data_env = NULL;
	while (data->env[i])
	{
		data_env = ft_get_var_name(data->env[i]);
		if (var_name != NULL
			&& ft_strncmp(data_env, var_name, ft_strlen(var_name)) == 0
			&& ft_strlen(data_env) == ft_strlen(var_name))
		{
			flag = TRUE;
		}
		free(data_env);
		i++;
	}
	return (flag);
}

char	*ft_get_var_name(char *av)
{
	int		end;
	char	*var_name;
	int		equal_sign;

	end = 0;
	var_name = NULL;
	equal_sign = FALSE;
	while (av[end])
	{
		if (av[end] == '=')
		{
			equal_sign = TRUE;
			break ;
		}
		end++;
	}
	if (equal_sign == FALSE)
		return (NULL);
	var_name = malloc(sizeof(char) * (end + 1));
	if (var_name == NULL)
		return (NULL);
	ft_strlcpy(var_name, av, end + 1);
	return (var_name);
}

int	ft_count_arg(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		i++;
	}
	return (i);
}

void	ft_free_var_names(char **av, int arg_num)
{
	int	i;

	i = 0;
	while (i < arg_num - 1)
	{
		free(av[i]);
		i++;
	}
	free(av);
}
