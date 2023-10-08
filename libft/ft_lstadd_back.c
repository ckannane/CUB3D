/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 00:02:34 by ckannane          #+#    #+#             */
/*   Updated: 2023/01/26 19:45:28 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*end;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	end = ft_lstlast(*lst);
	end -> next = new;
	new -> next = NULL;
}

 int main()
 {
	 t_list *a;
	 t_list *b;
	 t_list *c;

	 a = malloc (sizeof(t_list));
	 b = malloc (sizeof(t_list));
	 c = malloc (sizeof(t_list));

	a->content = (char*)"hello";
	b->content = (char*)"holla";
	c->content = (char*)"salam";
	a -> next = b;
	b -> next = NULL;

	ft_lstadd_back(&a,c);

	while(a)
	{
		printf("%s \n",a->content);
		a = a -> next;
	}
 }