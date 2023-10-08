/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 22:15:04 by ckannane          #+#    #+#             */
/*   Updated: 2023/01/26 20:03:28 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst -> next != NULL)
		lst = lst -> next;
	return (lst);
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
	b -> next = c;
	c-> next = NULL;

		printf("%s \n",ft_lstlast(a)->content);

 }