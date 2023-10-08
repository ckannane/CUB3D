/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 22:06:46 by ckannane          #+#    #+#             */
/*   Updated: 2023/02/15 19:24:08 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
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

	ft_lstadd_front(&a,c);

	while(a)
	{
		printf("%s \n",a->content);
		a = a -> next;
	}
 }