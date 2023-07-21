/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:27:39 by ycardona          #+#    #+#             */
/*   Updated: 2023/07/21 15:26:06 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_count_pipes(char *input) //counts number of pipes
{
	int	i;
	int j;
	int	count;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '"') //skipp the pipes in " "
		{
			i++;
			j = 0;
			while (input[i + j])
			{
				if (input[i + j] == '"')
				{
					i += j;
					break;
				}
				j++;
			}
		}
		if (input[i] == 39) //skipp the pipes in ' '
		{
			i++;
			j = 0;
			while (input[i + j])
			{
				if (input[i + j] == 39)
				{
					i += j;
					break;
				}
				j++;
			}
		}
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

static int	ft_count_args(char const *s) //counts number of arguments
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == 34) //skipp the pipes in " "
		{
			j = 1;
			while (s[i + j])
			{
				if (s[i + j] == 34)
				{
					i += j + 1;
					if (s[i] == ' ')
						count++;
					break;
				}
				j++;
			}
		}
		if (s[i] == 39) //skipp the pipes in ' '
		{
			j = 1;
			while (s[i + j])
			{
				if (s[i + j] == 39)
				{
					i += j + 1;
					if (s[i] == ' ')
						count++;
					break;
				}
				j++;
			}
		}
		if (s[i] != ' ' && s[i])
		{
			j = 0;
			while (s[i + j] != ' ' && s[i + j])
				j++;
			count++;
			i = i + j - 1;
		}
		i++;
	}
	return (count);
}

char	*ft_substr_pipe(char *str, unsigned long *start) //returns the substring before the pipe as string 
{
	char	*sub;
	int		i;
	
	if (ft_strlen(str) < *start)
		return (NULL);
	i = 0;
	while (str[*start + i] && str[*start + i] != '|')
		i++;
	sub = (char *) malloc(i + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, str + *start, i + 1);
	*start += i + 1;
	return (sub);
}

int	ft_split_sub(char *sub_str, char *tokens[])
{
	int i;
	int	j;
	int	argc;

	i = 0;
	argc = 0;
	while(sub_str[i])
	{
		if (sub_str[i] == 34) //handling " "
		{
			j = 1;
			while (sub_str[i + j])
			{
				if (sub_str[i + j] == 34)
				{
					tokens[argc] = malloc(sizeof(char) * (j));
					if (tokens[argc] == NULL)
						exit (1);
					tokens[argc] = ft_memmove(tokens[argc], sub_str + i + 1, j - 1);
					tokens[argc][j - 1] = '\0';
					argc++;
					i += j + 1;
					break ;
				}
				j++;
			}
		}
		if (sub_str[i] == 39) //handling ' '
		{
			j = 1;
			while (sub_str[i + j])
			{
				if (sub_str[i + j] == 39) 
				{
					tokens[argc] = malloc(sizeof(char) * (j));
					if (tokens[argc] == NULL)
						exit (1);
					tokens[argc] = ft_memmove(tokens[argc], sub_str + i + 1, j - 1);
					tokens[argc][j - 1] = '\0';
					//check here for $!! 
					argc++;
					i += j + 1;
					break ;
				}
				j++;
			}
		}
		if (sub_str[i] != ' ')
		{
			j = 0;
			while (sub_str[i + j] != ' ' && sub_str[i + j])
				j++;
			tokens[argc] = malloc(sizeof(char) * (j + 1));
			if (tokens[argc] == NULL)
				exit (1);
			tokens[argc] = ft_memmove(tokens[argc], sub_str + i, j);
			tokens[argc][j] = '\0';
			argc++;
			i += j - 1;
		}
		i++;
	}
	return (0);
}

int	ft_add_path(char *funct_name, int i, t_data *data)
{
	data->tokens[i][0] = ft_strjoin("/bin/", funct_name);
	free(funct_name);
	return (0);
}

int	ft_parse(t_data *data)
{
	char	*input;
	int		i;
	unsigned long start;
	char	*sub_str;
	int		argc;

	input = readline(NULL); //add_history?
	data->pipe_num = ft_count_pipes(input);
	data->tokens = malloc(sizeof(char) * (data->pipe_num + 1)); //no NULL termination because we know pipe_num
	if (data->tokens == NULL)
		exit (1);
	i = 0;
	start = 0;
	while (i <= data->pipe_num)
	{
		sub_str = ft_substr_pipe(input, &start); //get substring untill pipe
		argc = ft_count_args(sub_str); //count arguments in substring
		printf("\n%d: %d\n", i, argc);

		data->tokens[i] = malloc(sizeof(char) * (argc + 1));
		if (data->tokens[i] == NULL)
			exit (1);
		ft_split_sub(sub_str, data->tokens[i]); //split and write the substring into tokens
		ft_add_path(data->tokens[i][0], i, data);
		data->tokens[i][argc] = NULL; //NULL-termination required for execve, works on linux! doesnt work  for printf on mac..
		free(sub_str); // --> problems with free and pointers on mac not on Linux!
		i++;
	}
	free(input);
	return (0);
}
