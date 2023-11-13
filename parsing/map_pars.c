/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:48:09 by otelliq           #+#    #+#             */
/*   Updated: 2023/11/12 11:39:15 by ckannane         ###   ########.fr       */
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

void	re_fill_size_map(t_bjt *p, char **tmp)
{
	int	j;
	int	big_len;
	int	len_malloc;
	int	i;

	j = 0;
	len_malloc = 0;
	while (tmp[len_malloc])
		len_malloc++;
	len_malloc++;
	p->mini_map = (char **)malloc(sizeof(char*) * (len_malloc + 1));
	big_len = ft_len(tmp) +1;
	i = 0;
	while(tmp[i] != NULL)
	{
		p->mini_map[i] = malloc(sizeof(char)*big_len+1);
		j = 0;
		while(tmp[i][j] != '\0')
		{
			if(tmp[i][j] == ' ')
				p->mini_map[i][j] = '1';
			else
				p->mini_map[i][j] = tmp[i][j];
			j++;
		}
		while(j < big_len - 1)
			p->mini_map[i][j++] = '1';
		p->mini_map[i][j] = '\0';
		i++;
	}
	p->mini_map[i++] = ft_calloc(big_len,1);
	p->mini_map[i] = NULL;
}

void	fill_map(t_bjt *m_d)
{
	int len = 0;
	int i = check_to_fill(m_d);
	int j = 0;
	char **tmp;
	while(m_d->file[len])
		len++;
	tmp = (char **)malloc(sizeof(char*) * len - i);
	if((check_to_fill(m_d)))
	{
		while(m_d->file[i])
		{
			if( (m_d->file[i]))
			tmp[j++] = ft_strdup(m_d->file[i]);
			i++;
		}
		tmp[j] = NULL;
		if(!borders_checker(tmp))
		{
			printf("Invalid map!\n");
			exit(1);
		}
		re_fill_size_map(m_d,tmp);
		free_double_array(tmp);
	}
	else if(!check_to_fill(m_d))
	{
		printf("Invalid map!\n");
		exit(1);
	}
}

int	check_to_fill(t_bjt *m_d)
{
	int i = 6;
	int j;
	int componentCounts[2] = {0};
	while(m_d->file[i])
	{
		j = 0;
		while(m_d->file[i][j])
		{
			if(m_d->file[i][j] != ' ' && m_d->file[i][j] != '\n' && m_d->file[i][j] != '1'
			&& m_d->file[i][j] != '0'&& m_d->file[i][j] != 'N' && m_d->file[i][j] != '\t')
				return 0;
			else if(m_d->file[i][j] == '\n')
				componentCounts[0]++;
			else if(m_d->file[i][j] == '1')
				componentCounts[1]++;
			j++;
		}
		if(componentCounts[0] >= 0 && componentCounts[1] > 2)
			return i;
		i++;
	}
	return 0;
}
int	ft_len(char **mini_map)
{
	int len;
    int longest = 0;
    int i = 0;

    while (mini_map[i])
	{
        if (mini_map[i])
		{
            len = ft_strlen(mini_map[i]);
            if (len > longest)
                longest = len;
        }
        i++;
    }
    return longest;
}
