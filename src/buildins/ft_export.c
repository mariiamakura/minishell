/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:52:26 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/07 16:09:43 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_export(char *av[], t_data *data, int index)
{
	char **var_names;
	int i;
	int arg_num;

	var_names = NULL;
	i = 0;
	arg_num = count_arg(av);
/* 	if (count_arg(av) == 0)
		//show env with declare -x or something */
	var_names = get_multi_var_name(av, arg_num);
	if (var_names == NULL)
		return ;
	while (i < arg_num - 1)
	{
		if (var_names[i] == NULL)
			i++;
		else if (is_var_in_env(data, var_names[i]) == TRUE)
		{
			data->env = replace_env_var(av[i + 1], data, var_names[i]);
		}
		else 
		{
			data->env = add_env_var(av[i + 1], data);
			if (data->env == NULL)
			{
				ft_putstr_fd("minishell: export", STDERR_FILENO);
				return ;
			}
		}
		i++;
	}
	index++;
	ft_free_2d(var_names);
}

char **replace_env_var(char *av, t_data *data, char *var_name)
{
	int i;
	char *new_var;
	char *data_env;

	i = 0;
	new_var = ft_strdup(av);
	data_env = NULL;
	if (new_var == NULL)
		return(NULL);
	while (data->env[i])
	{
		data_env = get_var_name(data->env[i]);
		if (ft_strncmp(data_env, var_name, ft_strlen(var_name)) == 0 && 
			ft_strlen(data_env) == ft_strlen(var_name))
		{
				data->env[i] = new_var;
		}
		free(data_env);
		i++;
	}
	return (data->env);
}

char **add_env_var(char *av, t_data *data)
{
	int size;
	char *new_var;

	size = count_arg(data->env);
	new_var = ft_strdup(av);
	if (new_var == NULL)
		return (NULL);
	data->env[size] = new_var;
	data->env[size + 1] = NULL;
	return (data->env);
}

int count_arg(char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		i++;
	}
	return (i);
}

int is_var_in_env(t_data *data, char *var_name)
{
	int i;
	int flag;
	int size;
	char *data_env;
	
	i = 0;
	flag = FALSE;
	size = 0;
	data_env = NULL;
	while (data->env[i])
	{
		data_env = get_var_name(data->env[i]);
		if (ft_strncmp(data_env, var_name, ft_strlen(var_name)) == 0 && 
			ft_strlen(data_env) == ft_strlen(var_name))
		{
			flag = TRUE;
		}
		free(data_env);
		i++;
	}
	return (flag);
}



char **get_multi_var_name(char **av, int num_var)
{
	int i;
	char **var_names;
	int j;
	
	i = 1;
	j = 0;
	var_names = malloc(sizeof(char *) * num_var);
	if (var_names == NULL)
		return (NULL);
	while (av[i])
	{
		var_names[j] = get_var_name(av[i]);
		i++;
		j++;
	}
	var_names[j] = NULL;
	return(var_names);
	
}

char *get_var_name(char* av)
{
	int end;
	char *var_name;
	int equal_sign;
	
	end = 0;
	var_name = NULL;
	equal_sign = FALSE;
	while (av[end])
	{
		if (av[end] == '=')
		{
			equal_sign = TRUE;
			break;
		}
		end++;
	}
	if (equal_sign == FALSE)
		return(NULL);
	var_name = malloc(sizeof(char) * (end + 1));
	if (var_name == NULL)
		return (NULL);
	ft_strlcpy(var_name, av, end + 1);
	return (var_name);
}