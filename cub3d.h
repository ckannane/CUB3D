/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:25:54 by ckannane          #+#    #+#             */
/*   Updated: 2023/11/17 01:29:38 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include <sys/stat.h>
# include <math.h>

# define SQ 50
# define WIDE 1400
# define HEIGHT 700

typedef struct s_img
{
	void	*img;
	int		i_width;
	int		i_height;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;


typedef struct s_bjt
{
	void			*mlx;
	void			*win;
	char			**file;
	char			**mini_map;
	char			**tmp;
	mlx_image_t		*wall;
	mlx_image_t		*sprite;
	mlx_image_t		*ground;
	mlx_image_t		*angle;
	mlx_image_t		*shadow;
	mlx_texture_t	*passing;
	mlx_texture_t	*texture;
	mlx_texture_t	*north;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*door_open;
	mlx_texture_t	*door_closed;
	int				door_detected;
	char			*Floor_color;
	char			*sky_color;
	char			**Floor_color1;
	char			**sky_color1;
	double			p_angle;
	double			r_angle;
	double			l_angle;
	double			p_x;
	double			p_y;
	double			tmp_x;
	double			tmp_y;
	double			rotat_x;
	double			rotat_y;
	double			dist;
	double			rays;
	double			h_x;
	double			h_y;
	double			v_x;
	double			v_y;
	double			dis_v;
	double			dis_h;
	double			wall_height;
	char 			*c;
	char			**NO;
	char			**WE;
	char			**EA;
	char			**SO;
	int				floor_R;
	int				floor_G;
	int				floor_B;
	int				sky_R;
	int				sky_G;
	int				sky_B;
	int				map_size_hight;
	int				map_size_wide;
	int				moves;
	int				mous_x;
	int				mous_y;
	int				reset;
	float			ray_ax;
	float			ray_ay;
	float 			fac;
	int				breaking;
	int				rewind;
	int				fps;
	int				NO_norm;
	int				SO_norm;
	int				WE_norm;
	int				EA_norm;
	int				C_norm;
	int				F_norm;
}t_bjt;

void	ft_colors(t_bjt *p);
void	ft_texture(t_bjt *m_d);
void	fill_map(t_bjt *m_d);
char	*check(char *str);
int	cub_checker(char *haystack, char *needle);
int	tex_checker(char *haystack, char *needle);
int	check_to_fill(t_bjt *m_d, int count_b, int count_a);
int	ft_len(char **mini_map);
void	checker00(t_bjt *m_c);
void ft_texture_check(t_bjt *m_d);
void render(t_bjt *map);
void key_hook(void* map);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void move_s(t_bjt *p);
void move_a(t_bjt *p);
void move_d(t_bjt *p);
void move_w(t_bjt *p);
int	step_check(t_bjt *p);
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void my_mlx_pixel_put(t_img *data, int x, int y, int color);
float	degree_to_radians(float degree);
int32_t    get_color_from_pos(mlx_texture_t *walli, int y, int x);
void	normilatation_angle(double *angle);
void dda(t_bjt *p, int xx, int y,int yy);
void    east_texture(t_bjt *p, int x, int y, float dist_top);
void    west_texture(t_bjt *p, int x, int y, float dist_top);
void    south_texture(t_bjt *p, int x, int y, float dist_top);
void    north_texture(t_bjt *p, int x, int y, float dist_top);
void	ray_vertical(t_bjt *p);
void	ray_horizon(t_bjt *p);
void	chech_vertical_value(t_bjt *p);
void	chech_horizon_value(t_bjt *p);
void	procces_the_rendring(t_bjt *p);
void	fix_the_value(int *start, int *end);
int		ft_hight_size(char **map);
void	exit_now(t_bjt *p);
void	get_value(t_bjt *p);
int		colon_size(char **av);
char	**read_map(char **av, int size);
int	borders_checker(t_bjt *m_d);
void	free_double_array(char **str);
int	touch_wall_hori(t_bjt *p);
int	touch_wall_ver(t_bjt *p);
void	ft_free_struct(t_bjt *p);
void	free_double_array(char **str);
int border_check(char **m_d);
void zero_check(t_bjt *m_d);
int	one_check(t_bjt *m_d);
int	check_to_check(t_bjt *m_d);
int	tab_check(t_bjt *m_d);
int	component_check(t_bjt *m_d);
int	player_checker(char **av);
void	dup_component_check(t_bjt *m_d);
void	erroc_exit(t_bjt *p, char *text);
#endif