/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 18:25:54 by ckannane          #+#    #+#             */
/*   Updated: 2023/10/08 22:17:17 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
//#include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include "libft/libft.h"
# include <sys/stat.h>
# include <mlx.h>
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
	t_img	wall;
	t_img	player;
	t_img	ground;
	float	p_angle;
	float		p_j;
	float		p_i;
	int		moves;
}t_bjt;

#endif