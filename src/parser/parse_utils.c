/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:30:14 by ycardona          #+#    #+#             */
/*   Updated: 2023/08/04 17:02:58 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_quotation(char *str, int *i, int quot)
{
	int	j;

	if (str[*i] == quot)
	{
		j = 1;
		while (str[*i + j])
		{
			if (str[*i + j] == quot)
			{
				*i += j;
				break ;
			}
			j++;
		}
	}
}

int	ft_count_pipes(char *input)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (input[0] == '|')
		exit (-1); //add the correct error message
	while (input[i])
	{
		ft_quotation(input, &i, 34);
		ft_quotation(input, &i, 39);
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

static void	ft_skipp_redir(char *str, int *i, int *count)
{
	if (str[*i] == '>' || str[*i] == '<')
	{
		if (0 < *i && str[*i - 1] != ' ')
			*count += 1;
		if ((str[*i] == '>' && str[*i + 1] == '>')
			|| (str[*i] == '<' && str[*i + 1] == '<'))
			*i += 1;
		if (str[*i + 1] == ' ')
		{
			*i += 1;
			while (str[*i] == ' ')
				*i += 1;
			if (!str[*i])
				*i -= 1;
		}
	}
}

int	ft_count_args(char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i])
		{
			while (s[i] != ' ' && s[i])
			{
				ft_quotation(s, &i, 34);
				ft_quotation(s, &i, 39);
				ft_skipp_redir(s, &i, &count);
				i++;
			}
			count++;
			i--;
		}
		i++;
	}
	return (count);
}

char	*ft_substr_pipe(char *str, unsigned long *start)
{
	char	*sub;
	int		i;

	i = *start;
	while (str[i] && str[i] != '|')
	{
		ft_quotation(str, &i, 34);
		ft_quotation(str, &i, 39);
		i++;
	}
	sub = (char *) malloc(i - *start + 1);
	if (sub == NULL)
		return (NULL);
	ft_memmove(sub, str + *start, i - *start + 1);
	sub[i - *start] = '\0';
	*start = i + 1;
	return (sub);
}
