/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:25:37 by ckannane          #+#    #+#             */
/*   Updated: 2023/10/08 22:15:22 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	exit_now(t_bjt *map)
{
	mlx_destroy_window(map->mlx, map->win);
	exit(0);
}

void	putground(t_bjt *p, int i, int j)
{
	mlx_put_image_to_window(p->mlx, p->win, p->ground.img, i, j);
}

void	putwall(t_bjt *p, int i, int j)
{
	mlx_put_image_to_window(p->mlx, p->win, p->wall.img, i, j);
}

void	putplayer(t_bjt *p, int i, int j)
{
	mlx_put_image_to_window(p->mlx, p->win, p->player.img, i, j);
}


void	print_map(t_bjt *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->mini_map[i])
	{
		j = 0;
		while (map->mini_map[i][j])
		{
			if (map->mini_map[i][j] == '1')
			{
				putground(map, 32 * j, 32 * i);
				putwall(map, 32 * j, 32 * i);
			}
			else
				putground(map, 32 * j, 32 * i);
			j++;
		}
		i++;
	}
	putplayer(map, map->p_i, map->p_j);
}
void	move_a(t_bjt *p)
{
	p->p_i-= (sin(p->p_angle) + cos(p->p_angle));
	print_map (p);
	putplayer(p, p->p_i, p->p_j);
}

void	move_d(t_bjt *p)
{
	p->p_i+= (sin(p->p_angle) + cos(p->p_angle));
	print_map (p);
	putplayer(p, p->p_i, p->p_j);
}

void	move_w(t_bjt *p)
{
	p->p_j -= (sin(p->p_angle) + cos(p->p_angle));
	print_map (p);
	putplayer(p, p->p_i, p->p_j);

}

void	move_s(t_bjt *p)
{
	p->p_j += (sin(p->p_angle) + cos(p->p_angle));
	print_map (p);
	putplayer(p, p->p_i, p->p_j);
}
void	right_rot(t_bjt *p)
{
	p->p_angle += 10;
	putplayer(p,p->p_i,p->p_j);
}

void	left_rot(t_bjt *p)
{
	p->p_angle -= 10;
	putplayer(p,p->p_i,p->p_j);
}

int	key_hook(int keycode, t_bjt *p)
{
	if (keycode == 0)
		move_a(p);
	if (keycode == 1)
		move_s(p);
	if (keycode == 2)
		move_d(p);
	if (keycode == 13)
		move_w(p);
	if (keycode == 53)
		exit_now(p);
	if (keycode == 123)
		right_rot(p);
	if (keycode == 124)
		left_rot(p);
	return (0);
}

void	render(int height, int wide, t_bjt *map)
{
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, 32 * wide, 32 * height, "so_Long");
	map->ground.img = mlx_xpm_file_to_image(map->mlx, "textures/ground.xpm", \
	&map->ground.i_width, &map->ground.i_height);
	map->player.img = mlx_xpm_file_to_image(map->mlx, "textures/player.xpm", \
	&map->player.i_width, &map->player.i_height);
	map->wall.img = mlx_xpm_file_to_image(map->mlx, "textures/wall.xpm", \
	&map->wall.i_width, &map->wall.i_height);
	print_map (map);
	mlx_hook (map->win, 2, 0, key_hook, map);
	mlx_hook (map->win, 17, 0, exit_now, map);
	mlx_loop (map->mlx);
}

int	colon_size(char **av)
{
	int		i;
	char	*str;
	int		fd;

	i = 0;
	fd = open(av[1], O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		free (str);
		str = get_next_line(fd);
		i++;
	}
	free (str);
	return (i);
}

char	*ft_strjoin_spc(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL )
		return ((char *)s2);
	if (s2 == NULL )
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

char	**read_map(char **av, int size)
{
	char	**map;
	char	*tmp;
	char	*new;
	int		fd;
	int		i;

	i = 0;
	fd = open(av[1], O_RDONLY);
	tmp = get_next_line(fd);
	while (i < size)
	{
		new = get_next_line(fd);
		tmp = ft_strjoin(tmp, new);
		free (new);
		i++;
	}
	map = ft_split(tmp, '\n');
	free (tmp);
	return (map);
}

void	setup(t_bjt *map, int i, int j, int n)
{
	while (map->mini_map[i])
	{
		j = 0;
		while (map->mini_map[i][j])
		{
			if (map->mini_map[i][j] == 'P')
			{
				map->p_j = 32 * i;
				map->p_i = 32 * j;
			}
			j++;
		}
		i++;
	}
	map->p_angle = 90;
}

int main(int ac, char **av)
{
	t_bjt	*map;
	int		wide;
	int		height;

	map = malloc(sizeof(t_bjt));
	height = colon_size(av);
	map->mini_map = read_map(av, height);
	setup(map, 0, 0, 0);
	wide = ft_strlen(map->mini_map[0]);
	render(height, wide, map);
	return (0);
}
