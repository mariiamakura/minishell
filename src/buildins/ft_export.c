/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparasku <mparasku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:52:26 by mparasku          #+#    #+#             */
/*   Updated: 2023/08/04 17:58:17 by mparasku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ft_export(char *av[], t_data *data, int index)
{
	char **var_names;
	int i;

	var_names = NULL;
	i = 0;
/* 	if (count_arg(av) == 0)
		//show env with declare -x or something */
	var_names = get_multi_var_name(av);
	if (var_names == NULL)
	{
		ft_putstr_fd("minishell: export", STDERR_FILENO);
		return ;
	}
	while (var_names[i])
	{
		if (is_var_in_env(data, var_names[i]) == TRUE)
			printf("var in env!");
			//var replace in env
		else 
		{
			data->env = add_env_var(av[i + 1], data/* , var_names[i] */);
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

char **add_env_var(char *av, t_data *data/* , char *var_name */)
{
	int size;
	char *new_var;

	size = count_arg(data->env);
	// if (var_has_value(var_name) == FALSE || no_space_after_equal(var_name) == FALSE)
	// 	return (NULL);
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
	
	i = 0;
	flag = FALSE;
	while (data->env[i]) 
	{
		if (ft_strncmp(data->env[i], var_name, ft_strlen(var_name)) == 0) //if env[i] "CAR" and var_name "CA" trits as the same
		{
			printf("%zu\n", ft_strlen(var_name));
			flag = TRUE;
		}
		i++;
	}
	return (flag);
}

int no_space_after_equal(char *var_name)
{
	char *new_var;

	new_var = var_name;
	new_var = ft_strchr(new_var, '=');
	if (new_var == NULL)
		return (FALSE);
	if (*(new_var + 1) == ' ')
		return (FALSE);
	return(TRUE);
	
}

int var_has_value(char *var_name)
{
	int i;
	int flag; //whether "=" found
	
	i = 0;
	flag = FALSE;
	while(var_name[i])
	{
		if (var_name[i] == ' ' && flag == FALSE)
			break;
		else if (var_name[i] == '=')
			flag = TRUE;		
	}
	return (flag);
}

char **get_multi_var_name(char **av)
{
	int i;
	int num_var;
	char **var_names;
	int j;
	
	i = 1;
	j = 0;
	num_var = count_arg(av);
	var_names = malloc(sizeof(char *) * num_var);
	if (var_names == NULL)
		return (NULL);
	while (av[i])
	{
		var_names[j] = get_var_name(av[i]);
		if (var_names[j] == NULL)
			return (NULL);
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
	
	end = 0;
	var_name = NULL;
	while (av[end] != '=' && av[end])
	{
		end++;
	}
	var_name = malloc(sizeof(char) * (end + 1));
	if (var_name == NULL)
		return (NULL);
	ft_strlcpy(var_name, av, end + 1);
	return (var_name);
}