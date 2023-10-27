/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:25:37 by ckannane          #+#    #+#             */
/*   Updated: 2023/10/16 20:12:16 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
void my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int exit_now(t_bjt *map)
{
	exit(0);
}

int	step_check(t_bjt *p)
{
	if ((p->mini_map[(int)(p->p_y) / 50][(int)p->tmp_x / 50] != '1'
        && p->mini_map[(int)p->tmp_y/50][(int)(p->p_x - (1 /2) ) / 50] != '1'
        && p->mini_map[(int)(p->tmp_y)/50][(int)p->tmp_x/50] != '1'))
		return 1;
	return 0;
}
//void putground(t_bjt *p, int i, int j)
//{
//	mlx_put_pixel(p->ground,i, j, 0xffffff);
//}

void putwall(t_bjt *p, int i, int j)
{
	mlx_image_to_window(p->mlx, p->wall, 50 * i, 50 * j);;
}

int	rays_simulation(t_bjt *p,int in, double z)
{
	int i;
	int j;
	int XL;
	int YL;
	XL =  in * (sin(z));
	YL =  in * (cos(z));
	double x = p->p_x;
	double y = p->p_y;
	i = (y + YL)/ 50;
	j = (x + XL)/ 50;
	if(p->mini_map[j][i] != '1')
		return 1;
	return 0;
}

//int	dont_hit_the_wall(t_bjt *p,int in, double z)
//{
//	int i;
//	int j;
//	double x = p->p_x;
//	double y = p->p_y;

//	if (mlx_is_key_down(p->mlx, MLX_KEY_A))
//	{
//		y += 3 * sin(z);
//		x -= 3 * cos(z);
//	}
//	if (mlx_is_key_down(p->mlx, MLX_KEY_S))
//	{
//		y -= 3 * sin(z);
//		x -= 3 * cos(z);
//	}
//	if (mlx_is_key_down(p->mlx, MLX_KEY_D))
//	{
//		y -= 3 * sin(z);
//		x += 3 * cos(z);
//	}
//	if (mlx_is_key_down(p->mlx, MLX_KEY_W))
//	{
//		y += 3 * sin(z);
//		x += 3 * cos(z);
//	}
//	j = y / 50;
//	i = x / 50;
//	if(p->mini_map[i][j] == '1')
//		return 0;
//	return 1;
//}

//void putplayer(t_bjt *p, double i, double j)
//{
//	//mlx_image_to_window(p->mlx, p->player, i, j);
//	int in = 0;
//	int	jn = 0;
//	mlx_delete_image(p->mlx, p->player);
//	p->player = mlx_new_image(p->mlx, 32 * p->map_size_wide,  32 * p->map_size_hight);
//	mlx_image_to_window(p->mlx, p->player, 0, 0);
//	while(in < 4)
//	{
//		jn = 0;
//		while (jn < 4)
//		{
//			mlx_put_pixel(p->player,p->p_y + jn, p->p_x + in, ft_pixel(255,0,0,255));
//			jn++;
//		}
//		in++;
//	}
//	//mlx_delete_image(p->mlx, p->player);
//	//p->player = mlx_new_image(p->mlx, p->p_y,  p->p_x);
//	//mlx_image_to_window(p->mlx, p->angle, 15, 0);
//	//mlx_image_to_window(p->mlx, p->angle, i + in, j + in);
//}
// int abs(int n) { return ((n > 0) ? n : (n * (-1))); }

// DDA Function for line generation
void DDA(t_bjt *p, float X0, float Y0, float X1, float Y1)
{
    // calculate dx & dy
    float dx = X1 - X0;
    float dy = Y1 - Y0;

   // calculate steps required for generating pixels
   int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

   // calculate increment in x & y for each steps
   float Xinc = dx / (float)steps;
   float Yinc = dy / (float)steps;

   // Put pixel for each step
   float X = X0;
   float Y = Y0;
   for (int i = 0; i <= steps; i++) {
       mlx_put_pixel(p->angle,X,Y,ft_pixel(0,255,0,255));
       X += Xinc; // increment in x at each step
       Y += Yinc; // increment in y at each step
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
			{
				putwall(map, 1 * j, 1 * i);
			}
			j++;
		}
		i++;
	}
	//putplayer(map, map->p_y, map->p_x);
}


void move_a(t_bjt *p)
{
	p->tmp_x = p->p_x + 3 * sin(p->p_angle);
	p->tmp_y = p->p_y - 3 * cos(p->p_angle);
	if (step_check(p))
	{
		p->p_x = p->tmp_x;
		p->p_y = p->tmp_y;
	}
}

void move_d(t_bjt *p)
{
	p->tmp_x = p->p_x - 3 * sin(p->p_angle);
	p->tmp_y = p->p_y + 3 * cos(p->p_angle);
	if (step_check(p))
	{
		p->p_x = p->tmp_x;
		p->p_y = p->tmp_y;
	}
}

void move_w(t_bjt *p)
{
	p->tmp_x = p->p_x + 3 * cos(p->p_angle);
	p->tmp_y = p->p_y + 3 * sin(p->p_angle);
	if (step_check(p))
	{
		p->p_x = p->tmp_x;
		p->p_y = p->tmp_y;
	}
}

void move_s(t_bjt *p)
{
	p->tmp_x = p->p_x - 3 * cos(p->p_angle);
	p->tmp_y = p->p_y - 3 * sin(p->p_angle);
	if (step_check(p))
	{
		p->p_x = p->tmp_x;
		p->p_y = p->tmp_y;
	}
}
void right_rot(t_bjt *p)
{
	p->p_angle += 0.01;
	// p->l_angle += 0.3;
	// p->r_angle += 0.3;
}

void left_rot(t_bjt *p)
{
	p->p_angle -= 0.01;
	// p->l_angle -= 0.3;
	// p->r_angle -= 0.3;
}

void key_hook(void* map)
{
	t_bjt *p;

	p = map;
	//printf("%d\n",keycode.key);
	//if(dont_hit_the_wall(p,0,p->p_angle))
	//{
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
	//}
		if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
			exit_now(p);
		if (mlx_is_key_down(p->mlx, MLX_KEY_RIGHT))
			right_rot(p);
		if (mlx_is_key_down(p->mlx, MLX_KEY_LEFT))
			left_rot(p);

	if (p->p_angle > 2 * M_PI)
		p->p_angle = 0;
	if(p->p_angle < 0)
		p->p_angle += 2*M_PI;
	//if ((p->mini_map[(int)(p->tmp_x - (1 /2)) / 50][(int)p->tmp_y / 50] != '1'
    //    || p->mini_map[(int)p->tmp_x/50][(int)(p->tmp_y - (1 /2) ) / 50] != '1'
    //    || p->mini_map[(int)(p->tmp_x + (1 /2))/50][(int)p->tmp_y/50] != '1'
    //    || p->mini_map[(int)p->tmp_x/50][(int)(p->tmp_y + (1 /2))/50] != '1'))
	//{
	//	p->p_x = p->tmp_x;
	//	p->p_y = p->tmp_y;
	//}
	int in = 0;
	int jn = 0;
	int yu = 0;
	int XL;
	int YL;

	p->rotat_x = sin(p->p_angle);
	p->rotat_y = cos(p->p_angle);
	mlx_delete_image(p->mlx, p->angle);
	p->angle =  mlx_new_image(p->mlx, 50 * p->map_size_wide, 50 * p->map_size_hight);
	mlx_image_to_window(p->mlx, p->angle, 0, 0);
		while(yu < 6)
		{
			jn = 0;
			while (jn < 6)
			{
				mlx_put_pixel(p->angle,p->p_x + jn - 3, p->p_y + yu - 3, ft_pixel(255,0,0,255));
				jn++;
			}
			yu++;
		}

		//while(dont_hit_the_wall(p,in,p->p_angle)==1)
		//{
		//	XL =  in * (p->rotat_x);
		//	YL =  in * (p->rotat_y);
		//	mlx_put_pixel(p->angle,p->p_y + YL, p->p_x + XL, ft_pixel(0,255,0,255));
		//	in++;
		//}
		// double rays = p->r_angle;
		// while (rays <= p->l_angle)
		// {
		// 	in = 0;
		// 	while(rays_simulation(p,in,rays))
		// 	{
		// 		XL =  in * (sin(rays));
		// 		YL =  in * (cos(rays));
		// 		mlx_put_pixel(p->angle,p->p_y + YL, p->p_x + XL, ft_pixel(0,255,0,255));
		// 		in++;
		// 	}
		// 	rays += 0.001;
		// }
		float AX;
		float AY;
		AY = (int)(p->p_y/50) * 50;
		if(p->p_angle > 0 && p->p_angle < M_PI)
			AY += 50;
		AX = p->p_x + (AY - p->p_y)/tan(p->p_angle);
		if((AX <= p->map_size_wide*50 && AX >= 0 && AY <= p->map_size_hight*50 && AY >= 0))
		if(p->mini_map[(int)(AY/50)][(int)(AX/50)] != '1'&& p->mini_map[(int)(AY-1)/50][(int)(AX/50)] != '1')
		while(1)
		{
			if(p->p_angle > 0 && p->p_angle < M_PI)
				AY += 50;
			else
				AY -= 50;
			AX = p->p_x + (AY - p->p_y)/tan(p->p_angle);
			if(AX > p->map_size_wide*50 || AX <0)
				break;
			if(p->mini_map[(int)(AY/50)][(int)(AX/50)] == '1' || p->mini_map[(int)(AY-1)/50][(int)(AX/50)] == '1')
				break;
		}
		if(AX > p->map_size_wide*50)
			AX=p->map_size_wide*50-50;
		if(AX <0)
			AX=0;
		DDA(p,p->p_x,p->p_y,AX,AY);

		// in = 0;
		// while(in < 50)
		// {
		// 	XL =  in * (cos(p->p_angle));
		// 	YL =  in * (sin(p->p_angle));
		// 	mlx_put_pixel(p->angle,p->p_x + XL, p->p_y + YL, ft_pixel(255,0,255,255));
		// 	in++;
		// }
		//printf("distance from player to the wall = %d\nthe right view size = %d\nthe left view size = %d\n",in,(in/cos(30),));
	//putplayer(p, p->p_y , p->p_x);
}

void render(int height, int wide, t_bjt *map)
{
	map->mlx = mlx_init(50 * map->map_size_wide, 50 * map->map_size_hight, "CUB3D", true);
	map->walli = mlx_load_png("textures/images.png");
	map->angle =  mlx_new_image(map->mlx, 50 * map->map_size_wide,  50 * map->map_size_hight);
	map->player = mlx_new_image(map->mlx, 50 * map->map_size_wide,  50 * map->map_size_hight);
	map->wall = mlx_texture_to_image(map->mlx, map->walli);
	print_map(map);
	//putplayer(map, map->p_y, map->p_x);
	mlx_image_to_window(map->mlx, map->player, 0, 0);
	mlx_image_to_window(map->mlx, map->angle, 0, 0);
	mlx_loop_hook(map->mlx, key_hook, map);
	//mlx_delete_image(map->mlx, map->player);
	mlx_loop(map->mlx);
}

int colon_size(char **av)
{
	int i;
	char *str;
	int fd;

	i = 0;
	fd = open(av[1], O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i++;
	}
	free(str);
	return (i);
}

char *ft_strjoin_spc(char *s1, char *s2)
{
	size_t i;
	size_t j;
	char *str;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = ' ';
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char **read_map(char **av, int size)
{
	char **map;
	char *tmp;
	char *new;
	int fd;
	int i;

	i = 0;
	fd = open(av[1], O_RDONLY);
	tmp = get_next_line(fd);
	while (i < size)
	{
		new = get_next_line(fd);
		tmp = ft_strjoin(tmp, new);
		free(new);
		i++;
	}
	map = ft_split(tmp, '\n');
	free(tmp);
	return (map);
}

void setup(t_bjt *map, int i, int j, int n)
{
	while (map->mini_map[i])
	{
		j = 0;
		while (map->mini_map[i][j])
		{
			if (map->mini_map[i][j] == 'P')
			{
				map->p_y = 50 * i;
				map->p_x = 50 * j;
			}
			j++;
		}
		i++;
	}
	map->p_angle = M_PI/2;
	map->l_angle = 2*M_PI/3;
	map->r_angle = M_PI/3;
}

int main(int ac, char **av)
{
	t_bjt *map;
	int wide;
	int height;

	map = malloc(sizeof(t_bjt));
	map->map_size_hight = colon_size(av);
	map->mini_map = read_map(av, map->map_size_hight);
	setup(map, 0, 0, 0);
	map->map_size_wide = ft_strlen(map->mini_map[0]);
	render(height, wide, map);
	return (0);
}
