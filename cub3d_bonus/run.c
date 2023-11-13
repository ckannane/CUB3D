/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:27:29 by ckannane          #+#    #+#             */
/*   Updated: 2023/11/13 17:38:43 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_it(t_bjt *p, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i <= 10)
	{
		j = 0;
		while (j <= 10)
		{
			mlx_put_pixel(p->angle, x+j, y+i, color);
			j++;
		}
		i++;
	}
}
void	print_player(t_bjt *p)
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
			mlx_put_pixel(p->angle, (p->p_x/50*10)+j, (p->p_y/50*10)+i, ft_pixel(0,255,0,255));
			j++;
		}
		i++;
	}
}

void print_map(t_bjt *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map->mini_map[i])
	{
		j = 0;
		while (map->mini_map[i][j])
		{
			if (map->mini_map[i][j] == '1')
				print_it(map, j*10, i*10,ft_pixel(255,255,255,150));
			if (map->mini_map[i][j] == '2' || map->mini_map[i][j] == '3')
				print_it(map, j*10, i*10,ft_pixel(255,0,255,150));
			j++;
		}
		i++;
	}
	print_player(map);
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

void	dda_bns(t_bjt *p, int xx, int y, int yy)
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
			if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '2' || 
				p->mini_map[((int)p->ray_ay)/50][((int)p->ray_ax-1)/50] == '2')
				render_wall_h(p, xx, y, dist_top);
			else if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '3' || 
				p->mini_map[((int)p->ray_ay)/50][((int)p->ray_ax-1)/50] == '3')
				render_crack_h(p, xx, y, dist_top);
			else if (cos(p->rays) > 0)
				east_texture(p, xx, y, dist_top);
			else
				west_texture(p, xx, y, dist_top);
		}
		else
		{
			if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '2' || 
				p->mini_map[((int)p->ray_ay-1)/50][((int)p->ray_ax)/50] == '2')
				render_wall_v(p, xx, y, dist_top);
			else if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '3' || 
				p->mini_map[((int)p->ray_ay-1)/50][((int)p->ray_ax)/50] == '3')
				render_crack_v(p, xx, y, dist_top);
			else if (sin(p->rays) > 0)
				north_texture(p, xx, y, dist_top);
			else
				south_texture(p, xx, y, dist_top);
		}
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
	if (tmp_mous_x < p->mous_x && tmp_mous_x > 0 && tmp_mous_x < WIDE && tmp_mous_y > 0 && tmp_mous_y < HEIGHT)
	{
		p->p_angle -= degree_to_radians(2);
	 	p->mous_x = tmp_mous_x;
		p->mous_y = tmp_mous_y;
	}
	if (tmp_mous_x > p->mous_x && tmp_mous_x > 0 && tmp_mous_x < WIDE && tmp_mous_y > 0 && tmp_mous_y < HEIGHT)
	{
		p->p_angle += degree_to_radians(2);
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
	return (0);
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
			p->mini_map[(int)(p->h_y - 1) / SQ][(int)(p->h_x / SQ)] != '3')
			)
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
			p->mini_map[(int)(p->v_y) / SQ][(int)((p->v_x - 1) / SQ)] != '3')
			)
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
	}
	chech_vertical_value(p);
}

void	procces_the_rendring_b(t_bjt *p)
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
		p->fac = p->east->height / p->wall_height;
		dda_bns(p, rays, start, end);
		rays++;
	}
}
void	break_wall(t_bjt *p)
{
	if(p->dist <= 50)
		p->breaking++;
	if(p->breaking == 3 && p->dist <= 50)
	{
		if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '2')
			p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] = '3';
		if (p->mini_map[((int)p->ray_ay)/50][((int)p->ray_ax-1)/50] == '2')
			p->mini_map[(int)p->ray_ay/50][((int)p->ray_ax-1)/50] = '3';
		if (p->mini_map[((int)p->ray_ay-1)/50][((int)p->ray_ax)/50] == '2')
			p->mini_map[((int)p->ray_ay-1)/50][(int)p->ray_ax/50] = '3';
		p->reset = 1;
	}
	else if(p->breaking <= 7 && p->dist <= 50 && p->reset == 1)
	{
		p->door_open = mlx_load_png("textures/animation/3.png");
 		p->reset = 2;
	}
	else if(p->breaking <= 12 && p->dist <= 50 && p->reset == 2)
	{
		p->door_open = mlx_load_png("textures/animation/4.png");
		p->reset = 3;
	}
	else if(p->breaking <= 15 && p->dist <= 50 && p->reset == 3)
	{
		p->door_open = mlx_load_png("textures/animation/5.png");
		p->reset = 4;
	}
	else if(p->breaking >= 22 && p->reset == 4)
	{
		if (p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] == '3' )
			p->mini_map[(int)p->ray_ay/50][(int)p->ray_ax/50] = '0';
		if (p->mini_map[((int)p->ray_ay)/50][((int)p->ray_ax-1)/50] == '3')
			p->mini_map[(int)p->ray_ay/50][((int)p->ray_ax-1)/50] = '0';
		if (p->mini_map[((int)p->ray_ay-1)/50][((int)p->ray_ax)/50] == '3')
			p->mini_map[((int)p->ray_ay-1)/50][(int)p->ray_ax/50] = '0';
		p->breaking = 0;
		p->reset = 0;
	}
}

void key_hook_b(void* map)
{
	t_bjt	*p;

	p = map;
	p->tmp_x = p->p_x;
	p->tmp_y = p->p_y;
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
	normilatation_angle(&p->p_angle);
	mlx_delete_image(p->mlx, p->angle);
		// mlx_image_to_window(p->mlx, p->sprite, WIDE/5, HEIGHT/5);
	p->angle = mlx_new_image(p->mlx, WIDE, HEIGHT);
	mlx_image_to_window(p->mlx, p->angle, 0, 0);
	p->door_detected = 0;
	procces_the_rendring_b(p);
	print_map(p);
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
	map->frames = mlx_load_png("textures/animation/frame1.png");
	map->angle =  mlx_new_image(map->mlx, WIDE,  HEIGHT);
	map->shadow = mlx_new_image(map->mlx, WIDE,  HEIGHT);
	// map->wall = mlx_texture_to_image(map->mlx, map->north);
	// map->wall = mlx_texture_to_image(map->mlx, map->south);
	// map->wall = mlx_texture_to_image(map->mlx, map->east);
	// map->wall = mlx_texture_to_image(map->mlx, map->east);
	map->sprite = mlx_texture_to_image(map->mlx, map->frames);
	//putplayer(map, map->p_y, map->p_x);
			int sky = 0;
			int i = 0;
			int blue = 0;
			int green = 0;
			int red = 255;
		while(sky < (HEIGHT)/2)
		{
			i =0;
			while(i <= WIDE)
				mlx_put_pixel(map->shadow,i++,sky,ft_pixel(red, green,blue,255));
			if(blue < 70)
				blue++;
			if(green < 255)
				green++;
			sky++;
		}
		 blue = 20;
		 green = 50;
		 red = 70;
		while(sky < HEIGHT)
		{
			i =0;
			while(i <= WIDE)
				mlx_put_pixel(map->shadow,i++,sky,ft_pixel(red, green,blue,255));
			if(blue < 50)
				blue++;
			if(green < 100)
				green++;
			if (red < 100)
			red++;
			sky++;
		}
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
	map->map_size_hight = ft_hight_size(map->mini_map);
	map->map_size_wide  = ft_len(map->mini_map);
	render_b(height, wide, map);
	return (0);
}

