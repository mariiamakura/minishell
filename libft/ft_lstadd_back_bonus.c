/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycardona <ycardona@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:26:49 by ycardona          #+#    #+#             */
/*   Updated: 2022/12/13 15:26:44 by ycardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last -> next = new;
}

/* int	main(void)
{
	t_list * l =  NULL;
	t_list * l2 =  NULL;
	ft_lstadd_back(&l, ft_lstnew("1"));
	ft_lstadd_back(&l, ft_lstnew("2"));
	ft_lstadd_back(&l2, ft_lstnew("3"));
	ft_lstadd_back(&l2, ft_lstnew("4"));
	ft_lstadd_back(&l, l2);
	printf("%s\n", (char *) l -> content);
	printf("%s\n%s\n", (char *) ((((((l->next))->next))->next)-> content), 
	(char *) (((((l->next))->next))->next)-> next);
} */