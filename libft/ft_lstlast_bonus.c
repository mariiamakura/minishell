/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:20:42 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/13 13:58:59 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (lst == NULL)
		return (NULL);
	last = lst;
	while (last -> next != NULL)
		last = last -> next;
	return (last);
}

/* int main(void)
{
	t_list	*lst;
	t_list	*first;
	t_list	*second;
	t_list	*current;
	
	lst = ft_lstnew("head");
	first = ft_lstnew("first");
	second = ft_lstnew("second");

	ft_lstadd_front(&lst, first);
	ft_lstadd_front(&lst, second);

	current = lst; 
	while (current != NULL)
	{
		printf("%s\n", (char *) current -> content);
		current = current -> next;
	}
	printf("%p\n", ft_lstlast(NULL));
} */