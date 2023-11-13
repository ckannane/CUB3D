/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:23:55 by ckannane          #+#    #+#             */
/*   Updated: 2023/11/12 17:28:05 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float	degree_to_radians(float degree)
{
	return (degree * M_PI / 180);
}

int32_t	get_color_from_pos(mlx_texture_t *walli, int y, int x)
{
	int	index;

	if (x >= 0 && x < (int)walli->width && y >= 0 && y < (int)walli->height)
	{
		index = (walli->width * y + x) * walli->bytes_per_pixel;
		return (ft_pixel(walli->pixels[index], walli->pixels[index + 1],
				walli->pixels[index + 2], 255));
	}
	return (ft_pixel(0, 0, 0, 0));
}

// void	procces_the_rendring(t_bjt *p)
// {
// 	int		rays;
// 	int		start;
// 	int		end;
// 	float	distance_project;

// 	rays = 0;
// 	while (rays < WIDE)
// 	{
// 		p->rays = rays / (float)WIDE + p->p_angle - M_PI / 6;
// 		normilatation_angle(&p->rays);
// 		ray_horizon(p);
// 		ray_vertical(p);
// 		get_value(p);
// 		p->dist = p->dist * cos(p->p_angle - p->rays);
// 		distance_project = (WIDE / 2) / tan(M_PI / 4);
// 		p->wall_height = (SQ / p->dist) * distance_project;
// 		if (p->wall_height < 0)
// 			p->wall_height *= -1;
// 		start = (HEIGHT / 2) - p->wall_height;
// 		end = (HEIGHT / 2) + p->wall_height;
// 		fix_the_value(&start, &end);
// 		p->fac = p->east->height / p->wall_height;
// 		dda(p, rays, start, end);
// 		rays++;
// 	}
// }
