/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:25:54 by ckannane          #+#    #+#             */
/*   Updated: 2023/10/16 12:38:01 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
#include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include <sys/stat.h>
//# include <mlx.h>
# include <math.h>

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
	void	*mlx;
	void	*win;
	char	**mini_map;
	mlx_image_t	*wall;
	mlx_image_t	*player;
	mlx_image_t	*ground;
	mlx_image_t	*angle;
	mlx_texture_t* texture;
	mlx_texture_t* walli;
	double	p_angle;
	double	r_angle;
	double	l_angle;
	double		p_x;
	double		p_y;
	double		tmp_x;
	double		tmp_y;
	double		rotat_x;
	double		rotat_y;
	int			map_size_hight;
	int			map_size_wide;
	int		moves;
}t_bjt;

#endif