/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:48:09 by otelliq           #+#    #+#             */
/*   Updated: 2023/11/17 01:29:14 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_colors(t_bjt *p)
{
	p->Floor_color1 = ft_split(p->Floor_color, ',');
	p->sky_color1 = ft_split(p->sky_color, ',');
	if (!p->Floor_color1[0] || !p->Floor_color1[1] || 
		!p->Floor_color1[2] || p->Floor_color1[3] || 
		!p->sky_color1[0] || !p->sky_color1[1] || 
		!p->sky_color1[2] || p->sky_color1[3])
		printf("Error, invalid RGB!\n");
	p->floor_R = ft_atoi(p->Floor_color1[0]);
	p->floor_G = ft_atoi(p->Floor_color1[1]);
	p->floor_B = ft_atoi(p->Floor_color1[2]);
	p->sky_R = ft_atoi(p->sky_color1[0]);
	p->sky_G = ft_atoi(p->sky_color1[1]);
	p->sky_B = ft_atoi(p->sky_color1[2]);
}

void	ft_texture(t_bjt *m_d)
{
	int	i;
	int	fd;

	i = 0;
	while (m_d->file[i])
	{
		if (tex_checker(m_d->file[i], "NO") == 1)
			m_d->NO = ft_split(m_d->file[i], ' ');
		if (tex_checker(m_d->file[i], "WE") == 1)
			m_d->WE = ft_split(m_d->file[i], ' ');
		if (tex_checker(m_d->file[i], "SO") == 1)
			m_d->SO = ft_split(m_d->file[i], ' ');
		if (tex_checker(m_d->file[i], "EA") == 1)
			m_d->EA = ft_split(m_d->file[i], ' ');
		if (tex_checker(m_d->file[i], "F") == 1) 
			m_d->Floor_color = check(m_d->file[i]);
		if (tex_checker(m_d->file[i], "C") == 1)
			m_d->sky_color = check(m_d->file[i]);
		i++;
	}
	ft_texture_check(m_d);
}

void	fill_with_ones(t_bjt *p, int big_len, char **tmp)
{
	int	i;
	int	j;

	i = 0;
	while (tmp[i] != NULL)
	{
		p->mini_map[i] = malloc(sizeof(char) * big_len + 1);
		j = 0;
		while (tmp[i][j] != '\0')
		{
			if (tmp[i][j] == ' ')
				p->mini_map[i][j] = '1';
			else
				p->mini_map[i][j] = tmp[i][j];
			j++;
		}
		while (j < big_len - 1)
			p->mini_map[i][j++] = '1';
		p->mini_map[i][j] = '\0';
		i++;
	}
	p->mini_map[i++] = ft_calloc(big_len, 1);
	p->mini_map[i] = NULL;
}

void	re_fill_size_map(t_bjt *p, char **tmp)
{
	int	big_len;
	int	len_malloc;

	len_malloc = 0;
	while (tmp[len_malloc])
		len_malloc++;
	len_malloc++;
	p->mini_map = (char **)malloc(sizeof(char *) * (len_malloc + 1));
	big_len = ft_len(tmp) + 1;
	fill_with_ones(p, big_len, tmp);
}

void	fill_map(t_bjt *m_d)
{
	int	len;
	int	i;
	int	j;

	len = 0;
	i = check_to_fill(m_d, 0, 0);
	j = 0;
	while (m_d->file[len])
		len++;
	m_d->tmp = (char **)malloc(sizeof(char *) * len - i);
	if ((check_to_fill(m_d, 0, 0)))
	{
		while (m_d->file[i])
		{
			if (m_d->file[i])
				m_d->tmp[j++] = ft_strdup(m_d->file[i]);
			i++;
		}
		m_d->tmp[j] = NULL;
		re_fill_size_map(m_d, m_d->tmp);
	}
	else if (!check_to_fill(m_d, 0, 0))
		erroc_exit(m_d, "Invalid map!");
}
