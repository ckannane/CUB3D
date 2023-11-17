/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:34:58 by ckannane          #+#    #+#             */
/*   Updated: 2023/11/17 01:43:27 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_double_array(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
}

void	ft_free_struct(t_bjt *p)
{
	if (p->mini_map)
		free_double_array(p->mini_map);
	if (p->file)
		free_double_array(p->file);
	if (p->Floor_color1)
		free_double_array(p->Floor_color1);
	if (p->sky_color1)
		free_double_array(p->sky_color1);
	if (p->NO)
		free_double_array(p->NO);
	if (p->WE)
		free_double_array(p->WE);
	if (p->EA)
		free_double_array(p->EA);
	if (p->SO)
		free_double_array(p->SO);
	if (p->sky_color)
		free(p->sky_color);
	if (p->Floor_color)
		free(p->Floor_color);
}

void	erroc_exit(t_bjt *p, char *text)
{
	printf("Error\n%s\n", text);
	ft_free_struct(p);
	pause();
	exit(1);
}
