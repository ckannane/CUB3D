/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:27:29 by ckannane          #+#    #+#             */
/*   Updated: 2023/11/17 14:06:30 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_it(t_bjt *p, int x, int y, int color, int fac)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i <= fac)
	{
		j = 0;
		while (j <= fac)
		{
			mlx_put_pixel(p->angle, x+j, y+i, color);
			j++;
		}
		i++;
	}
}
void	print_player(t_bjt *p, float fac)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i <= 1)
	{
		j = 0;
		while (j <= 1)
		{
			mlx_put_pixel(p->angle, ((p->p_x/50)*fac)+j, ((p->p_y/50)*fac)+i, ft_pixel(0,255,0,255));
			j++;
		}
		i++;
	}
}

void	print_map(t_bjt *map)
{
	int i;
	int j;
	float fac;
	
	i = 0;
	j = 0;
	if ((map->map_size_wide * SQ) / WIDE > (map->map_size_hight * SQ) / HEIGHT)
		fac = 10 / ((map->map_size_wide * SQ) / WIDE);
	else
		fac = 10 / ((map->map_size_hight * SQ) / HEIGHT);
	while (map->mini_map[i])
	{
		j = 0;
		while (map->mini_map[i][j])
		{
			if (map->mini_map[i][j] == '1')
				print_it(map, j * fac, i * fac, ft_pixel(255, 255, 255, 150),fac);
			if (map->mini_map[i][j] == '2' || map->mini_map[i][j] == '3')
				print_it(map, j * fac, i * fac, ft_pixel(255, 0, 255, 150), fac);
			if (map->mini_map[i][j] == '4')
				print_it(map, j * fac, i * fac, ft_pixel(0, 0, 255, 150), fac);
			j++;
		}
		i++;
	}
	print_player(map, fac);
}

void	render_door_h(t_bjt *p, int x, int y, float dist_top)
{
	int	color;
	int	offse_x;
	int	offse_y;

	offse_y = dist_top * p->fac / 2;
	offse_x = (int)p->ray_ay % p->east->width;
	color = get_color_from_pos(p->passing, offse_y, offse_x);
	mlx_put_pixel(p->angle, x, y, color);
}

void	render_crack_h(t_bjt *p, int x, int y, float dist_top)
{
	int	color;
	int	offse_x;
	int	offse_y;

	offse_y = dist_top * p->fac / 2;
	offse_x = (int)p->ray_ay % p->east->width;
	color = get_color_from_pos(p->door_open, offse_y, offse_x);
	mlx_put_pixel(p->angle, x, y, color);
}
void	render_door_v(t_bjt *p, int x, int y, float dist_top)
{
	int	color;
	int	offse_x;
	int	offse_y;

	offse_y = dist_top * p->fac / 2;
	offse_x = (int)p->ray_ax % p->east->width;
	color = get_color_from_pos(p->passing, offse_y, offse_x);
	mlx_put_pixel(p->angle, x, y, color);
}

void	render_crack_v(t_bjt *p, int x, int y, float dist_top)
{
	int	color;
	int	offse_x;
	int	offse_y;

	offse_y = dist_top * p->fac / 2;
	offse_x = (int)p->ray_ax % p->east->width;
	color = get_color_from_pos(p->door_open, offse_y, offse_x);
	mlx_put_pixel(p->angle, x, y, color);
}

void	render_wall_h(t_bjt *p, int x, int y, float dist_top)
{
	int	color;
	int	offse_x;
	int	offse_y;

	offse_y = dist_top * p->fac / 2;
	offse_x = (int)p->ray_ay % p->east->width;
	color = get_color_from_pos(p->door_closed, offse_y, offse_x);
	mlx_put_pixel(p->angle, x, y, color);
}
void	render_wall_v(t_bjt *p, int x, int y, float dist_top)
{
	int	color;
	int	offse_x;
	int	offse_y;

	offse_y = dist_top * p->fac / 2;
	offse_x = (int)p->ray_ax % p->east->width;
	color = get_color_from_pos(p->door_closed, offse_y, offse_x);
	mlx_put_pixel(p->angle, x, y, color);
}

void	put_horizontal_walls(t_bjt *p, int xx, int y, float dist_top)
{
	if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '2' || 
		p->mini_map[((int)p->ray_ay-1)/50][((int)p->ray_ax)/50] == '2')
			render_wall_v(p, xx, y, dist_top);
	else if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '3' || 
		p->mini_map[((int)p->ray_ay-1)/50][((int)p->ray_ax)/50] == '3')
		render_crack_v(p, xx, y, dist_top);
	else if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '4' || 
		p->mini_map[((int)p->ray_ay-1)/50][((int)p->ray_ax)/50] == '4')
		render_door_v(p, xx, y, dist_top);
	else if (sin(p->rays) > 0)
		north_texture(p, xx, y, dist_top);
	else
		south_texture(p, xx, y, dist_top);
}

void	put_vertical_walls(t_bjt *p, int xx, int y, float dist_top)
{
	if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '2' || 
		p->mini_map[((int)p->ray_ay)/50][((int)p->ray_ax-1)/50] == '2')
		render_wall_h(p, xx, y, dist_top);
	else if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '3' || 
		p->mini_map[((int)p->ray_ay)/50][((int)p->ray_ax-1)/50] == '3')
		render_crack_h(p, xx, y, dist_top);
	else if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '4' || 
		p->mini_map[((int)p->ray_ay)/50][((int)p->ray_ax-1)/50] == '4')
		render_door_h(p, xx, y, dist_top);
	else if (cos(p->rays) > 0)
		east_texture(p, xx, y, dist_top);
	else
		west_texture(p, xx, y, dist_top);
}

void	dda_bns(t_bjt *p, int xx, int y, int yy)
{
	int		i;
	float	j;
	float	dist_top;

	i = -1;
	j = yy - y;
	p->fac = p->east->height / p->wall_height;
	while (++i <= j)
	{
		dist_top = y + (p->wall_height) - (HEIGHT / 2);
		if (p->dis_h > p->dis_v)
			put_vertical_walls(p, xx, y, dist_top);
		else
			put_horizontal_walls(p, xx, y, dist_top);
		y++;
	}
}

void	mouse_mouves(t_bjt *p)
{
	int tmp_mous_x;
	int tmp_mous_y;

	tmp_mous_x = p->mous_x;
	tmp_mous_y = p->mous_y;
	mlx_get_mouse_pos(p->mlx,&tmp_mous_x,&tmp_mous_y);
	if (tmp_mous_x < p->mous_x && tmp_mous_x > 0 && 
		tmp_mous_x < WIDE && tmp_mous_y > 0 && tmp_mous_y < HEIGHT)
	{
		p->p_angle -= degree_to_radians(4);
	 	p->mous_x = tmp_mous_x;
		p->mous_y = tmp_mous_y;
	}
	if (tmp_mous_x > p->mous_x && tmp_mous_x > 0 && 
		tmp_mous_x < WIDE && tmp_mous_y > 0 && tmp_mous_y < HEIGHT)
	{
		p->p_angle += degree_to_radians(4);
		p->mous_x = tmp_mous_x;
		p->mous_y = tmp_mous_y;
	}
}

int	touch_wall_hori_b(t_bjt *p)
{
	if (p->h_x > p->map_size_wide * SQ || p->h_x < 0)
		return (1);
	if (p->mini_map[(int)(p->h_y / SQ)][(int)(p->h_x / SQ)] == '1' ||
		p->mini_map[(int)(p->h_y - 1) / SQ][(int)(p->h_x / SQ)] == '1')
		return (1);
	if (p->mini_map[(int)(p->h_y / SQ)][(int)(p->h_x / SQ)] == '2' ||
		p->mini_map[(int)(p->h_y - 1) / SQ][(int)(p->h_x / SQ)] == '2')
		{
			p->door_detected = 1;
			return (1);
		}
	if (p->mini_map[(int)(p->h_y / SQ)][(int)(p->h_x / SQ)] == '3' ||
		p->mini_map[(int)(p->h_y - 1) / SQ][(int)(p->h_x / SQ)] == '3')
		{
			p->door_detected = 1;
			return (1);
		}
	if (p->mini_map[(int)(p->h_y / SQ)][(int)(p->h_x / SQ)] == '4' ||
		p->mini_map[(int)(p->h_y - 1) / SQ][(int)(p->h_x / SQ)] == '4')
		{
			p->door_detected = 1;
			return (1);
		}
	return (0);
}

int	touch_wall_ver_b(t_bjt *p)
{
	if (p->v_y > p->map_size_hight * SQ || p->v_x > p->map_size_wide * SQ 
		|| p->v_y < 0 || p->v_x < 0)
		return (1);
	if (p->mini_map[(int)(p->v_y / SQ)][(int)(p->v_x / SQ)] == '1' || 
		p->mini_map[(int)(p->v_y) / SQ][(int)((p->v_x - 1) / SQ)] == '1')
		return (1);
	if (p->mini_map[(int)(p->v_y / SQ)][(int)(p->v_x / SQ)] == '2' || 
		p->mini_map[(int)(p->v_y) / SQ][(int)((p->v_x - 1) / SQ)] == '2')
		{
			p->door_detected = 1;
			return (1);
		}
	if (p->mini_map[(int)(p->v_y / SQ)][(int)(p->v_x / SQ)] == '3' || 
		p->mini_map[(int)(p->v_y) / SQ][(int)((p->v_x - 1) / SQ)] == '3')
		{
			p->door_detected = 1;
			return (1);
		}
	if (p->mini_map[(int)(p->v_y / SQ)][(int)(p->v_x / SQ)] == '4' || 
		p->mini_map[(int)(p->v_y) / SQ][(int)((p->v_x - 1) / SQ)] == '4')
		{
			p->door_detected = 1;
			return (1);
		}
	return (0);
}

void	ray_simulation_h(t_bjt *p)
{
	while (1)
	{
		if (p->rays > 0 && p->rays < M_PI)
			p->h_y += SQ;
		else
			p->h_y -= SQ;
		p->h_x = p->p_x + (p->h_y - p->p_y) / tan(p->rays);
		if (touch_wall_hori_b(p))
			break ;
	}
}
void	ray_simulation_v(t_bjt *p)
{
	while (1)
	{
		if (p->rays - 90 <= 0 && (p->rays <= M_PI / 2 || 
				p->rays >= 3 * M_PI / 2))
			p->v_x += SQ;
		else
			p->v_x -= SQ;
		p->v_y = p->p_y - (p->p_x - p->v_x) * tan(p->rays); 
		if (touch_wall_ver_b(p))
			break ;
	}
}


void	ray_horizon_b(t_bjt *p)
{
	p->h_y = (int)(p->p_y / SQ) * SQ;
	if (p->rays > 0 && p->rays < M_PI)
		p->h_y += SQ;
	p->h_x = p->p_x + (p->h_y - p->p_y) / tan(p->rays);
	if ((p->h_x <= p->map_size_wide * SQ && p->h_x >= 0 && 
			p->h_y <= p->map_size_hight * SQ && p->h_y >= 0))
	{
		if ((p->mini_map[(int)(p->h_y / SQ)][(int)(p->h_x / SQ)] != '1' &&
			p->mini_map[(int)(p->h_y - 1) / SQ][(int)(p->h_x / SQ)] != '1' )&&
			(p->mini_map[(int)(p->h_y / SQ)][(int)(p->h_x / SQ)] != '2' &&
			p->mini_map[(int)(p->h_y - 1) / SQ][(int)(p->h_x / SQ)] != '2')&&
			(p->mini_map[(int)(p->h_y / SQ)][(int)(p->h_x / SQ)] != '3' &&
			p->mini_map[(int)(p->h_y - 1) / SQ][(int)(p->h_x / SQ)] != '3')&&
			(p->mini_map[(int)(p->h_y / SQ)][(int)(p->h_x / SQ)] != '4' &&
			p->mini_map[(int)(p->h_y - 1) / SQ][(int)(p->h_x / SQ)] != '4')
			)
				ray_simulation_h(p);
	}
	chech_horizon_value(p);
}


void	ray_vertical_b(t_bjt *p)
{
	p->v_x = (int)(p->p_x / SQ) * SQ;
	if (p->rays - 90 <= 0 && (p->rays <= M_PI / 2 || p->rays >= 3 * M_PI / 2))
		p->v_x += SQ;
	p->v_y = p->p_y - (p->p_x - p->v_x) * tan(p->rays);
	if ((p->v_x <= p->map_size_wide * SQ && p->v_x >= 0 && 
			p->v_y <= p->map_size_hight * SQ && p->v_y >= 0))
	{
		if ((p->mini_map[(int)(p->v_y / SQ)][(int)(p->v_x / SQ)] != '1' && 
			p->mini_map[(int)(p->v_y) / SQ][(int)((p->v_x - 1) / SQ)] != '1' )&&
			(p->mini_map[(int)(p->v_y / SQ)][(int)(p->v_x / SQ)] != '2' && 
			p->mini_map[(int)(p->v_y) / SQ][(int)((p->v_x - 1) / SQ)] != '2')&&
			(p->mini_map[(int)(p->v_y / SQ)][(int)(p->v_x / SQ)] != '3' && 
			p->mini_map[(int)(p->v_y) / SQ][(int)((p->v_x - 1) / SQ)] != '3')&&
			(p->mini_map[(int)(p->v_y / SQ)][(int)(p->v_x / SQ)] != '4' && 
			p->mini_map[(int)(p->v_y) / SQ][(int)((p->v_x - 1) / SQ)] != '4')
			)
				ray_simulation_v(p);
	}
	chech_vertical_value(p);
}

void	break_the_wall(t_bjt *p)
{
	int	i;
	int	j;

	i = -1;
	while(p->mini_map[++i])
	{
		j = -1;
		while(p->mini_map[i][++j])
		{
			if (p->mini_map[i][j] == '3' && p->breaking == 7)
				p->door_open = mlx_load_png("textures/animation/2.png");
			if (p->mini_map[i][j] == '3' && p->breaking == 14)
				p->door_open = mlx_load_png("textures/animation/3.png");
			if (p->mini_map[i][j] == '3' && p->breaking == 21)
				p->door_open = mlx_load_png("textures/animation/4.png");
			if (p->mini_map[i][j] == '3' && p->breaking == 28)
				p->door_open = mlx_load_png("textures/animation/5.png");
			if (p->mini_map[i][j] == '3' && p->breaking == 35)
			{
				p->mini_map[i][j] = '4';
				p->breaking = 0; 
			}
		}
	}
}
void	fix_the_wall(t_bjt *p)
{
	int	i;
	int	j;

	i = -1;
	while(p->mini_map[++i])
	{
		j = -1;
		while(p->mini_map[i][++j])
		{
			if (p->mini_map[i][j] == '3' && p->reset == 7)
				p->door_open = mlx_load_png("textures/animation/5.png");
			if (p->mini_map[i][j] == '3' && p->reset == 14)
				p->door_open = mlx_load_png("textures/animation/4.png");
			if (p->mini_map[i][j] == '3' && p->reset == 21)
				p->door_open = mlx_load_png("textures/animation/3.png");
			if (p->mini_map[i][j] == '3' && p->reset == 28)
				p->door_open = mlx_load_png("textures/animation/2.png");
			if (p->mini_map[i][j] == '3' && p->reset == 35)
			{
				p->mini_map[i][j] = '2';
				p->reset = 0; 
			}
		}
	}
}


void	fix_wall(t_bjt *p)
{
	if( (int)p->dist <= 100)
	{
		if (p->mini_map[((int)p->ray_ay)/50][((int)p->ray_ax-1)/50] == '4')
			p->mini_map[(int)p->ray_ay/50][((int)p->ray_ax-1)/50] = '3';
		if (p->mini_map[((int)p->ray_ay-1)/50][((int)p->ray_ax)/50] == '4')
			p->mini_map[((int)p->ray_ay-1)/50][(int)p->ray_ax/50] = '3';
		p->reset = 1;
	}
}

void	break_wall(t_bjt *p)
{
	if( (int)p->dist <= 100)
	{
		if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '2')
			p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] = '3';
		if (p->mini_map[((int)p->ray_ay)/50][((int)p->ray_ax-1)/50] == '2')
			p->mini_map[(int)p->ray_ay/50][((int)p->ray_ax-1)/50] = '3';
		if (p->mini_map[((int)p->ray_ay-1)/50][((int)p->ray_ax)/50] == '2')
			p->mini_map[((int)p->ray_ay-1)/50][(int)p->ray_ax/50] = '3';
		if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '4')
			p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] = '3';
			p->breaking = 1;
	}
}

void	open_close_door(t_bjt *p)
{
	if (mlx_is_key_down(p->mlx, MLX_KEY_SPACE))
		break_wall(p);
	if (mlx_is_key_down(p->mlx, MLX_KEY_C))
		fix_wall(p);
}

void	procces_the_rendring_b(t_bjt *p)
{
	int		rays;
	int		start;
	int		end;
	float	distance_project;

	rays = -1;
	while (++rays < WIDE)
	{
		p->rays = rays / (float)WIDE + p->p_angle - M_PI / 6;
		normilatation_angle(&p->rays);
		ray_horizon_b(p);
		ray_vertical_b(p);
		get_value(p);
		p->dist = p->dist * cos(p->p_angle - p->rays);
		distance_project = (WIDE / 2) / tan(M_PI / 4);
		p->wall_height = (SQ / p->dist) * distance_project;
		if (p->wall_height < 0)
			p->wall_height *= -1;
		start = (HEIGHT / 2) - p->wall_height;
		end = (HEIGHT / 2) + p->wall_height;
		fix_the_value(&start, &end);
		open_close_door(p);
		dda_bns(p, rays, start, end);
	}
}
void	commands(t_bjt *p)
{
	if (mlx_is_key_down(p->mlx, MLX_KEY_A))
		move_a(p);
	if (mlx_is_key_down(p->mlx, MLX_KEY_S))
		move_s(p);
	if (mlx_is_key_down(p->mlx, MLX_KEY_D))
		move_d(p);
	if (mlx_is_key_down(p->mlx, MLX_KEY_W))
		move_w(p);
	if (mlx_is_key_down(p->mlx, MLX_KEY_SPACE))
		break_wall(p);
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		exit_now(p);
	if (mlx_is_key_down(p->mlx, MLX_KEY_RIGHT))
		p->p_angle += degree_to_radians(2);
	if (mlx_is_key_down(p->mlx, MLX_KEY_LEFT))
		p->p_angle -= degree_to_radians(2);
	mouse_mouves(p);
}
void	water_fall(t_bjt *p)
{
	if (p->fps == 3)
	{
		p->north = mlx_load_png("textures/animation/water_fall/north/wn_1.png");
		p->south = mlx_load_png("textures/animation/water_fall/south/wn_1.png");
		p->east = mlx_load_png("textures/animation/water_fall/east/wn_1.png");
		p->west = mlx_load_png("textures/animation/water_fall/west/wn_1.png");
	}
	if (p->fps == 6)
	{
		p->north = mlx_load_png("textures/animation/water_fall/north/wn_2.png");
		p->south = mlx_load_png("textures/animation/water_fall/south/wn_2.png");
		p->east = mlx_load_png("textures/animation/water_fall/east/wn_2.png");
		p->west = mlx_load_png("textures/animation/water_fall/west/wn_2.png");
	}
	if (p->fps == 9)
	{
		p->north = mlx_load_png("textures/animation/water_fall/north/wn_3.png");
		p->south = mlx_load_png("textures/animation/water_fall/south/wn_3.png");
		p->east = mlx_load_png("textures/animation/water_fall/east/wn_3.png");
		p->west = mlx_load_png("textures/animation/water_fall/west/wn_3.png");
	}
	if (p->fps == 12)
	{
		p->north = mlx_load_png("textures/animation/water_fall/north/wn_4.png");
		p->south = mlx_load_png("textures/animation/water_fall/south/wn_4.png");
		p->east = mlx_load_png("textures/animation/water_fall/east/wn_4.png");
		p->west = mlx_load_png("textures/animation/water_fall/west/wn_4.png");
	}
	if (p->fps == 15)
	{
		p->north = mlx_load_png("textures/animation/water_fall/north/wn_5.png");
		p->south = mlx_load_png("textures/animation/water_fall/south/wn_5.png");
		p->east = mlx_load_png("textures/animation/water_fall/east/wn_5.png");
		p->west = mlx_load_png("textures/animation/water_fall/west/wn_5.png");
		p->fps = 0;
	}
}

void key_hook_b(void* map)
{
	t_bjt	*p;

	p = map;
	p->tmp_x = p->p_x;
	p->tmp_y = p->p_y;
	commands(p);
	normilatation_angle(&p->p_angle);
	mlx_delete_image(p->mlx, p->angle);
	if (p->breaking != 0)
		p->breaking++;
	if (p->reset != 0)
		p->reset++; 
	p->angle = mlx_new_image(p->mlx, WIDE, HEIGHT);
	mlx_image_to_window(p->mlx, p->angle, 0, 0);
	procces_the_rendring_b(p);
	break_the_wall(p);
	fix_the_wall(p);
	water_fall(p);
	p->fps++;
	print_map(p);
}

void	render_the_ground(t_bjt *p, int blue, int green, int red)
{
	int	sky;
	int	i;

	i = 0;
	sky = HEIGHT / 2;
	while(sky < HEIGHT)
	{
		i = 0;
		while(i <= WIDE)
			mlx_put_pixel(p->shadow, i++, sky, ft_pixel(red, green, blue, 255));
		if(blue <= 182)
			blue++;
		if(green <= 176)
			green++;
		if (red <= 121)
			red++;
		sky++;
	}
}

void	render_the_sun_set(t_bjt *p, int blue, int green, int red)
{
	int	sky;
	int	i;

	i = 0;
	sky = 0;
	while (sky < (HEIGHT)/2)
	{
		i = 0 ;
		while (i <= WIDE)
			mlx_put_pixel(p->shadow, i++, sky, ft_pixel(red, green, blue, 255));
		if (blue < 70)
			blue++;
		if (green < 255)
			green++;
		sky++;
	}
	render_the_ground(p,138,116,87);
}

void render_b(int height, int wide, t_bjt *map)
{
	map->mlx = mlx_init(WIDE, HEIGHT, "CUB3D", true);
	map->north = mlx_load_png("textures/red.png");
	map->west = mlx_load_png("textures/black.png");
	map->east = mlx_load_png("textures/sky.png");
	map->south = mlx_load_png("textures/green.png");
	map->door_closed = mlx_load_png("textures/animation/1.png");
	map->door_open = mlx_load_png("textures/animation/2.png");
	map->passing = mlx_load_png("textures/open_door.png");
	map->angle =  mlx_new_image(map->mlx, WIDE,  HEIGHT);
	map->shadow = mlx_new_image(map->mlx, WIDE,  HEIGHT);
	render_the_sun_set(map, 0, 0, 255);
	mlx_image_to_window(map->mlx, map->angle, 0, 0);
	mlx_image_to_window(map->mlx, map->shadow, 0, 0);
	mlx_loop_hook(map->mlx, key_hook_b, map);
	mlx_loop(map->mlx);
}

void setup(t_bjt *map, int i, int j, int n)
{
	while (map->mini_map[i])
	{
		j = 0;
		while (map->mini_map[i][j])
		{
			if (map->mini_map[i][j] == 'N' || map->mini_map[i][j] == 'E' 
			|| map->mini_map[i][j] == 'W' || map->mini_map[i][j] == 'S')
			{
				if (map->mini_map[i][j] == 'N')
					map->p_angle = 3*M_PI/2;
				else if (map->mini_map[i][j] == 'W')
					map->p_angle = 0;
				else if (map->mini_map[i][j] == 'E')
					map->p_angle = M_PI;
				else if (map->mini_map[i][j] == 'S')
					map->p_angle = M_PI/2;
				map->p_y = 50 * i + 25;
				map->p_x = 50 * j + 25;
			}
			j++;
		}
		i++;
	}
}

int main(int ac, char **av)
{
	t_bjt *map;
	int wide;
	int height;

	map = malloc(sizeof(t_bjt));
	height = colon_size(av);
	map->file = read_map(av, height);
	ft_texture(map);
	ft_colors(map);
	fill_map(map);
	setup(map, 0, 0, 0);
	map->mous_x = 0;
	map->mous_y = 0;
	map->breaking = 0;
	map->reset = 0;
	map->fps = 0;
	map->map_size_hight = ft_hight_size(map->mini_map);
	map->map_size_wide  = ft_len(map->mini_map);
	if(map->map_size_hight > 70 || map->map_size_wide > 70)
	{
		printf("\nERROR : the MAP is dam big\
		\nwhat you trying to do ??? GTA VI map ?!");
		exit(1);
	}
	render_b(height, wide, map);
	return (0);
}

