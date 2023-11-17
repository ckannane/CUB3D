/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 20:39:39 by ckannane          #+#    #+#             */
/*   Updated: 2023/11/17 01:35:19 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sky_ground(t_bjt *map)
{
	int	sky;
	int	i;

	i = 0;
	sky = 0;
	while (sky < HEIGHT / 2)
	{
		i = 0;
		while (i <= WIDE)
			mlx_put_pixel(map->shadow, i++, sky,
				ft_pixel(map->sky_R, map->sky_G, map->sky_B, 255));
		sky++;
	}
	while (sky < HEIGHT)
	{
		i = 0;
		while (i <= WIDE)
			mlx_put_pixel(map->shadow, i++, sky,
				ft_pixel(map->floor_R, map->floor_G, map->floor_B, 255));
		sky++;
	}
}

void	dda(t_bjt *p, int xx, int y, int yy)
{
	int		i;
	float	j;
	float	dist_top;

	i = -1;
	j = yy - y;
	while (++i <= j)
	{
		dist_top = y + (p->wall_height) - (HEIGHT / 2);
		if (p->dis_h > p->dis_v)
		{
			if (cos(p->rays) > 0)
				east_texture(p, xx, y, dist_top);
			else
				west_texture(p, xx, y, dist_top);
		}
		else
		{
			if (sin(p->rays) > 0)
				north_texture(p, xx, y, dist_top);
			else
				south_texture(p, xx, y, dist_top);
		}
		y++;
	}
}

void	procces_the_rendring(t_bjt *p)
{
	int		rays;
	int		start;
	int		end;
	float	distance_project;

	rays = 0;
	while (rays < WIDE)
	{
		p->rays = rays / (float)WIDE + p->p_angle - M_PI / 6;
		normilatation_angle(&p->rays);
		ray_horizon(p);
		ray_vertical(p);
		get_value(p);
		p->dist = p->dist * cos(p->p_angle - p->rays);
		distance_project = (WIDE / 2) / tan(M_PI / 4);
		p->wall_height = (SQ / p->dist) * distance_project;
		if (p->wall_height < 0)
			p->wall_height *= -1;
		start = (HEIGHT / 2) - p->wall_height;
		end = (HEIGHT / 2) + p->wall_height;
		fix_the_value(&start, &end);
		p->fac = p->east->height / p->wall_height;
		dda(p, rays, start, end);
		rays++;
	}
}

void	render(t_bjt *map)
{
	map->mlx = mlx_init(WIDE, HEIGHT, "CUB3D", true);
	map->north = mlx_load_png(map->NO[1]);
	map->west = mlx_load_png(map->WE[1]);
	map->east = mlx_load_png(map->EA[1]);
	map->south = mlx_load_png(map->SO[1]);
	if (!map->north || !map->south || !map->west || !map->east)
		erroc_exit(map, "texture no value");
	map->angle = mlx_new_image(map->mlx, WIDE, HEIGHT);
	map->shadow = mlx_new_image(map->mlx, WIDE, HEIGHT);
	sky_ground(map);
	mlx_image_to_window(map->mlx, map->angle, 0, 0);
	mlx_image_to_window(map->mlx, map->shadow, 0, 0);
	mlx_loop_hook(map->mlx, key_hook, map);
	mlx_loop(map->mlx);
}
