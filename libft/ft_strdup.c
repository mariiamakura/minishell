/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:04:07 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/09 15:15:38 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;

	dup = (char *) malloc(ft_strlen(s) + 1);
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, ft_strlen(s) + 1);
	return (dup);
}
