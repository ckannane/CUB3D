/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:21:24 by otelliq           #+#    #+#             */
/*   Updated: 2023/11/11 14:28:32 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	player_checker(char **av)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == 'N')
				count++;
			else if (av[i][j] == 'E')
				count++;
			else if (av[i][j] == 'S')
				count++;
			else if (av[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	borders_checker(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] == '0' && av[i][j + 1] == ' ') || \
			(av[i][j] == '0' && av[i][j - 1] == ' ') || \
			(av[i][j] == '0' && av[i + 1][j] == ' ') || \
			(av[i][j] == '0' && av[i - 1][j] == ' '))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_texture_path_check(t_bjt *m_d, int fd)
{
	fd = open(m_d->NO[1], O_RDONLY);
	if (fd == -1)
	{
		printf("NO: TEXTURE path not found");
		exit(1);
	}
	fd = open(m_d->WE[1], O_RDONLY);
	if (fd == -1)
	{
		printf("WE: TEXTURE path not found");
		exit(1);
	}
	fd = open(m_d->EA[1], O_RDONLY);
	if (fd == -1)
	{
		printf("EA: TEXTURE path not found");
		exit(1);
	}
	fd = open(m_d->SO[1], O_RDONLY);
	if (fd == -1)
	{
		printf("SO: TEXTURE path not found");
		exit(1);
	}
}

int	check_double_path(t_bjt *m_d, char *name)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (m_d->file[i])
	{
		if (tex_checker(m_d->file[i], name) == 1)
			count++;
		i++;
	}
	return (count);
}

void	ft_texture_check(t_bjt *m_d)
{
	int	i;
	int	fd;

	i = 0;
	ft_texture_path_check(m_d, fd);
	if (check_double_path(m_d, "NO") == 0 || 
		check_double_path(m_d, "WE") == 0 || 
		check_double_path(m_d, "SO") == 0 || 
		check_double_path(m_d, "EA") == 0 || 
		check_double_path(m_d, "F") == 0 || 
		check_double_path(m_d, "C") == 0)
	{
		printf("Error: Missing component!\n");
		exit(1);
	}
	if (check_double_path(m_d, "NO") > 1 || check_double_path(m_d, "WE") > 1
		|| check_double_path(m_d, "SO") > 1 || check_double_path(m_d, "EA") > 1
		|| check_double_path(m_d, "F") > 1 || check_double_path(m_d, "C") > 1)
	{
		printf("Error: Duplicate component found!\n");
		exit(1);
	}
}
