/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:52:26 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/14 15:15:10 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_export(char *av[], t_data *data, int index)
{
	char	**var_names;
	int		i;
	int		arg_num;

	var_names = NULL;
	i = 0;
	arg_num = ft_count_arg(av);
	if (ft_count_arg(av) == 1)
		return (ft_declare_x(data, index));
	var_names = ft_get_multi_var_name(av, arg_num, FT_EXPORT);
	if (var_names == NULL)
		return (1);
	last_exit_global = var_name_error_new(var_names, arg_num);
	last_exit_global = ft_export_loop(arg_num, data, var_names, av);
	ft_free_var_names(var_names, arg_num);
	return (last_exit_global);
}

int	ft_export_loop(int arg_num, t_data *data, char **var_names, char **av)
{
	int	i;

	i = 0;
	while (i < arg_num - 1)
	{
		if (var_names[i] == NULL)
			i++;
		else if (ft_is_var_in_env(data, var_names[i]) == TRUE)
		{
			if (ft_replace_env_var(av[i + 1], data, var_names[i]) == NULL)
				return (ft_print_error_buildins("minishell: export", ""));
			i++;
		}
		else 
		{
			if (ft_add_env_var(av[i + 1], data) == NULL)
				return (ft_print_error_buildins("minishell: export", ""));
			i++;
		}
	}
	if (last_exit_global != 0)
		return (last_exit_global);
	return (0);
}

char	**ft_replace_env_var(char *av, t_data *data, char *var_name)
{
	int		i;
	char	*new_var;
	char	*data_env;

	i = 0;
	new_var = ft_strdup(av);
	data_env = NULL;
	if (new_var == NULL)
		return (NULL);
	while (data->env[i])
	{
		data_env = ft_get_var_name(data->env[i]);
		if (ft_strncmp(data_env, var_name, ft_strlen(var_name)) == 0 && 
			ft_strlen(data_env) == ft_strlen(var_name))
		{
			free(data->env[i]);
			data->env[i] = new_var;
		}
		free(data_env);
		i++;
	}
	return (data->env);
}

char	**ft_add_env_var(char *av, t_data *data)
{
	int		size;
	char	*new_var;
	char	**new_env;

	size = ft_count_arg(data->env);
	new_env = malloc(sizeof(char *) * (size + 2));
	new_var = ft_strdup(av);
	if (new_var == NULL || new_env == NULL)
		return (NULL);
	size = 0;
	while (data->env[size])
	{
		new_env[size] = ft_strdup(data->env[size]);
		if (new_env[size] == NULL)
		{
			ft_free_2d(new_env);
			return (NULL);
		}
		size++;
	}
	new_env[size] = new_var;
	new_env[size + 1] = NULL;
	ft_free_2d(data->env);
	data->env = new_env;
	return (data->env);
}

char	**ft_get_multi_var_name(char **av, int num_var, int flag)
{
	int		i;
	char	**var_names;
	int		j;

	i = 1;
	j = 0;
	var_names = malloc(sizeof(char *) * num_var);
	if (var_names == NULL)
		return (NULL);
	while (av[i])
	{
		if (flag == FT_EXPORT)
			var_names[j] = ft_get_var_name(av[i]);
		else if (flag == FT_UNSET)
			var_names[j] = ft_strdup(av[i]);
		i++;
		j++;
	}
	var_names[j] = NULL;
	return (var_names);
}
