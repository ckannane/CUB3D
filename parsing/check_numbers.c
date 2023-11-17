/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 01:09:14 by ckannane          #+#    #+#             */
/*   Updated: 2023/11/17 01:31:29 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init(t_bjt *m_d)
{
	m_d->C_norm = 0;
	m_d->F_norm = 0;
	m_d->NO_norm = 0;
	m_d->EA_norm = 0;
	m_d->SO_norm = 0;
	m_d->WE_norm = 0;
}

void	ft_texture_check(t_bjt *m_d)
{
	int	i;

	i = 0;
	init(m_d);
	while (m_d->file[i])
	{
		if (tex_checker(m_d->file[i], "NO") == 1)
			m_d->NO_norm++;
		else if (tex_checker(m_d->file[i], "WE") == 1)
			m_d->WE_norm++;
		else if (tex_checker(m_d->file[i], "SO") == 1)
			m_d->SO_norm++;
		else if (tex_checker(m_d->file[i], "EA") == 1)
			m_d->EA_norm++;
		else if (tex_checker(m_d->file[i], "F") == 1)
			m_d->F_norm++;
		else if (tex_checker(m_d->file[i], "C") == 1)
			m_d->C_norm++;
		i++;
	}
	dup_component_check(m_d);
}

void	dup_component_check(t_bjt *m_d)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (m_d->NO_norm > 1 || m_d->SO_norm > 1 || m_d->WE_norm > 1 || 
			m_d->EA_norm > 1 || m_d->C_norm > 1 || m_d->F_norm > 1)
                erroc_exit(m_d, "Duplicate component found!");
		else if (m_d->NO_norm == 0 || m_d->SO_norm == 0 || m_d->WE_norm == 0 || 
			m_d->EA_norm == 0 || m_d->C_norm == 0 || m_d->F_norm == 0)
                erroc_exit(m_d, "Missing component!");
		i++;
	}
}

int	tab_check(t_bjt *m_d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (m_d->file[i])
	{
		j = 0;
		while (m_d->file[i][j])
		{
			if (m_d->file[i][j] == '\t')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

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
