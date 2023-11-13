/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:34:58 by ckannane          #+#    #+#             */
/*   Updated: 2023/11/10 20:35:21 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_double_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	ft_free_struct(t_bjt *p)
{
	free_double_array(p->mini_map);
	free_double_array(p->file);
	free_double_array(p->Floor_color1);
	free_double_array(p->sky_color1);
	free_double_array(p->NO);
	free_double_array(p->WE);
	free_double_array(p->EA);
	free_double_array(p->SO);
	free(p->sky_color);
	free(p->Floor_color);
}
