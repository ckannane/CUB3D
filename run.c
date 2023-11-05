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
float	degree_to_radians(float degree)
{
	return (degree * M_PI / 180);
}

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

// DDA Function for line generation
void DD_earth(t_bjt *p, int X0, int Y0, int X1, int Y1)
{
	int opacity = 0;
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;

   // calculate steps required for generating pixels
   int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

   // calculate increment in x & y for each steps
   float Xinc = dx / (float)steps;
   float Yinc = dy / (float)steps;

   // Put pixel for each step
   float X = X0;
   float Y = Y0;
	// if(p->wall_height < (p->map_size_hight*50)/2)
   for (int i = 0; i <= steps; i++) {
       mlx_put_pixel(p->angle,X,Y,ft_pixel(50,50,50,255));
       X += Xinc; // increment in x at each step
       Y += Yinc; // increment in y at each step
   }
}

void DD_sky(t_bjt *p, int X0, int Y0, int X1, int Y1)
{
	int opacity = 0;
    // calculate dx & dy
    int dx = X1 - X0;
    int dy = Y1 - Y0;

   // calculate steps required for generating pixels
   int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

   // calculate increment in x & y for each steps
   float Xinc = dx / (float)steps;
   float Yinc = dy / (float)steps;

   // Put pixel for each step
   float X = X0;
   float Y = Y0;
	// if(p->wall_height < (p->map_size_hight*50)/2)
   for (int i = 0; i <= steps; i++) {
       mlx_put_pixel(p->angle,X,Y,ft_pixel(0, 0,70,255));
       X += Xinc; // increment in x at each step
       Y += Yinc; // increment in y at each step
   }
}

int	get_position(double pos, int txtwidth)
{
	int	position;

	position = ((pos / 50) - (int)(pos / 50)) * txtwidth;
	return (position);
}

uint32_t get_pixel(t_bjt *p, float x, float y){
	int r = 0;
int g = 0;
int b = 0;
int a = 0;
	// if (x >= 0 && x < (int)p->walli->width && y >= 0 && y < (int)p->walli->height)
	// {
		int pos = ((y +  p->walli->width)*p->walli->bytes_per_pixel);
		pos = (y +p->walli->width * x) * p->walli->bytes_per_pixel;
    // return (ft_pixel(tex->pixels[index], tex->pixels[index + 1],
    //         tex->pixels[index + 2], tex->pixels[index + 3]));
		// printf("%d\n", pos);
		// usleep(100);
		r = p->walli->pixels[pos++];
		g = p->walli->pixels[pos++];
		b = p->walli->pixels[pos++];
		a = p->walli->pixels[pos];
	// }
	return ft_pixel(r,g,b,a);

}

int32_t    get_color_from_pos(t_bjt *p, int y, int x)
{
    int    index;

    index = (p->walli->width*y + x) * p->walli->bytes_per_pixel;
    return (ft_pixel(p->walli->pixels[index], p->walli->pixels[index + 1],
            p->walli->pixels[index + 2], p->walli->pixels[index + 3]));
}

void DDA(t_bjt *p, int X0, int Y0, int X1, int Y1, int color, float ax, float ay)
{
	int opacity = 0;
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
	// if(p->wall_height < (p->map_size_hight*50)/2)
	opacity = p->wall_height/((p->map_size_hight*50)/1.5) * 255;
	if(opacity <= 0)
		opacity = 0;
	if(opacity >= 255)
		opacity = 255;
	// float ytxt = get_position(X1,p->walli->height);
	float fac = p->walli->height/p->wall_height;
	// float xtxt = offse_X;
	int offse_X = (int)ay%50;
	// usleep(100);
	int offse_Y ;
   for (int i = 0; i <= steps; i++) {
	int dist_top = Y + (p->wall_height) - (HEIGHT/2);
		offse_Y =dist_top * fac / 2;
	if (p->dis_h > p->dis_v){
		if (cos(p->rays) > 0){
			color = get_color_from_pos(p,offse_Y,offse_X);
       		mlx_put_pixel(p->angle,X,Y,color);
		}
		else
       		mlx_put_pixel(p->angle,X,Y,color);
	}
	else
	{
			if (sin(p->rays) > 0){
				
       		mlx_put_pixel(p->angle,X,Y,color);
			}
		else
       		mlx_put_pixel(p->angle,X,Y,color);
	}
		// ytxt = i*50 + offse_X;
		X += Xinc; // increment in x at each step
		Y += Yinc; // increment in y at each step
	// printf("%d,%d\n",offse_X,offse_Y);
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
				putwall(map, 1 * j, 1 * i);
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
	p->p_angle += 0.05;
	// p->l_angle += 0.3;
	// p->r_angle += 0.3;
}

void left_rot(t_bjt *p)
{
	p->p_angle -= 0.05;
	// p->l_angle -= 0.3;
	// p->r_angle -= 0.3;
}

void	ray_horizon(t_bjt *p)
{
		if (p->rays > 2 * M_PI)
			p->rays -= 2*M_PI;
		if(p->rays < 0)
			p->rays += 2*M_PI;
		p->h_y = (int)(p->p_y/50) * 50;
		if(p->rays > 0 && p->rays < M_PI)
			p->h_y += 50;
		p->h_x = p->p_x + (p->h_y - p->p_y)/tan(p->rays);
		if((p->h_x <= p->map_size_wide*50 && p->h_x >= 0 && p->h_y <= p->map_size_hight*50 && p->h_y >= 0))
			if(p->mini_map[(int)(p->h_y/50)][(int)(p->h_x/50)] != '1'&& p->mini_map[(int)(p->h_y-1)/50][(int)(p->h_x/50)] != '1')
				while(1)
				{
					if(p->rays > 0 && p->rays < M_PI)
						p->h_y += 50;
					else
						p->h_y -= 50;
					p->h_x = p->p_x + (p->h_y - p->p_y)/tan(p->rays);
					if(p->h_x > p->map_size_wide*50 || p->h_x <0)
						break;
					if(p->mini_map[(int)(p->h_y/50)][(int)(p->h_x/50)] == '1' || p->mini_map[(int)(p->h_y-1)/50][(int)(p->h_x/50)] == '1')
						break;
				}
		if(p->h_x > p->map_size_wide*50)
			p->h_x = p->map_size_wide * 50;
		if(p->h_x < 0)
			p->h_x=0;
		p->dis_h = sqrt((p->p_y - p->h_y)*(p->p_y - p->h_y) + (p->p_x - p->h_x)*(p->p_x - p->h_x));
}

void	ray_vertical(t_bjt *p)
{
	p->v_x = (int)(p->p_x/50)*50;
	if(p->rays - 90 <= 0 && (p->rays <= M_PI/2 || p->rays >= 3*M_PI/2))
		p->v_x += 50;
	p->v_y = p->p_y - (p->p_x - p->v_x)*tan(p->rays);
	if((p->v_x <= p->map_size_wide*50 && p->v_x >= 0 && p->v_y<= p->map_size_hight*50 && p->v_y>= 0))
	if(p->mini_map[(int)(p->v_y/50)][(int)(p->v_x/50)] != '1'&& p->mini_map[(int)(p->v_y)/50][(int)((p->v_x-1)/50)] != '1')
	while(1)
	{
		if(p->rays - 90 <= 0 && (p->rays <= M_PI/2 || p->rays >= 3*M_PI/2))
			p->v_x += 50;
		else
			p->v_x -= 50;
		p->v_y= p->p_y - (p->p_x - p->v_x)*tan(p->rays); 
		if(p->v_y> p->map_size_hight*50 || p->v_x > p->map_size_wide*50 || p->v_y< 0 || p->v_x < 0)
			break;
		if(p->mini_map[(int)(p->v_y/50)][(int)(p->v_x/50)] == '1' || p->mini_map[(int)(p->v_y)/50][(int)((p->v_x-1)/50)] == '1')
			break;
	}
	if(p->v_y> p->map_size_hight*50 || (p->v_y< 0 && (p->rays > 0 && p->rays < M_PI)))
	p->v_y= p->map_size_hight*50;
	if(p->v_y< 0)
		p->v_y= 0;
	if(p->v_x > p->map_size_wide*50)
		p->v_x=p->map_size_wide*50;
	if(p->v_x <0)
		p->v_x=0;
	p->dis_v = sqrt((p->p_y - p->v_y)*(p->p_y - p->v_y) + (p->p_x - p->v_x)*(p->p_x - p->v_x));
}

void key_hook(void* map)
{
	t_bjt *p;

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
	if (mlx_is_key_down(p->mlx, MLX_KEY_ESCAPE))
		exit_now(p);
	if (mlx_is_key_down(p->mlx, MLX_KEY_RIGHT))
		right_rot(p);
	if (mlx_is_key_down(p->mlx, MLX_KEY_LEFT))
		left_rot(p);
	if (p->p_angle > 2 * M_PI)
	p->p_angle -= 2*M_PI;
	if(p->p_angle < 0)
	p->p_angle += 2*M_PI;
		

	int in = 0;
	int jn = 0;
	int yu = 0;
	int XL;
	int YL;

	mlx_delete_image(p->mlx, p->angle);
	p->angle =  mlx_new_image(p->mlx, WIDE, HEIGHT);
	mlx_image_to_window(p->mlx, p->angle, 0, 0);

		float save_AY;
		float save_AX;
		float dist_h;
		float dist_v;
		int rays = 0;

	while (rays < WIDE)
	{
		int color = 0;
		p->rays = rays/(float)WIDE  + p->p_angle - M_PI/6;
		ray_horizon(p);
		ray_vertical(p);
		float ax, ay;
		if(p->dis_h < p->dis_v)
		{
			ax = p->h_x;
			ay = p->h_y;
			p->dist = p->dis_h;
		}
		else{
			ax = p->v_x;
			ay = p->v_y;
			p->dist = p->dis_v;
		}
		p->dist = p->dist * cos(p->p_angle - p->rays);
		float distance_project = (WIDE/2) / tan(M_PI/4);
		 p->wall_height = (50/p->dist)*distance_project;
		if(p->wall_height < 0)
		p->wall_height *= -1;
		float start = (HEIGHT/2) - p->wall_height;
		float end = (HEIGHT/2) + p->wall_height;
		if(start < 0)
		start = 0;
		if(start > (HEIGHT/2))
		start = (HEIGHT/2);
		if(end > HEIGHT)
		end = HEIGHT;
		if(end < HEIGHT/2)
		end = HEIGHT/2;
		int opacity = 0;
			opacity = p->wall_height/(HEIGHT/2) * 255;
		if(opacity <= 0)
			opacity = 10;
		if(opacity >= 255)
			opacity = 255;
		color = ft_pixel(255,0,0,opacity);

		DDA(p,rays,start,rays,end,color, ax, ay);
		rays++;
	}
}

void render(int height, int wide, t_bjt *map)
{
	map->mlx = mlx_init(WIDE, HEIGHT, "CUB3D", true);
	map->walli = mlx_load_png("textures/black.png");
	map->angle =  mlx_new_image(map->mlx, WIDE,  HEIGHT);
	map->shadow = mlx_new_image(map->mlx, WIDE,  HEIGHT);
	map->wall = mlx_texture_to_image(map->mlx, map->walli);
	//putplayer(map, map->p_y, map->p_x);
	// print_map(map);
			int sky = 0;
		while(sky < (map->map_size_hight*50)/2)
		{
			DD_sky(map,0,sky,map->map_size_wide*50,sky);
			sky++;
		}
		while(sky < (map->map_size_hight*50))
		{
			DD_earth(map,0,sky,map->map_size_wide*50,sky);
			sky++;
		}
	mlx_image_to_window(map->mlx, map->shadow, 0, 0);
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
				map->p_y = 50 * i +25;
				map->p_x = 50 * j+25;
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

