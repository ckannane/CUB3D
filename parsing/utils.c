/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:41:45 by otelliq           #+#    #+#             */
/*   Updated: 2023/11/17 01:34:16 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	checker00(t_bjt *m_c)
{
	if (m_c->floor_R > 225 || m_c->floor_R < 0 || 
		m_c->floor_G > 225 || m_c->floor_G < 0 || 
		m_c->floor_B > 225 || m_c->floor_B < 0 || 
		m_c->sky_R > 225 || m_c->sky_R < 0 || 
		m_c->sky_G > 225 || m_c->sky_G < 0 || 
		m_c->sky_B > 225 || m_c->sky_B < 0)
		erroc_exit(m_c, "Error, invalid RGB!");
}

int	check_to_fill(t_bjt *m_d, int count_b, int count_a)
{
	int	i;
	int	j;

	i = 6;
	while (m_d->file[i])
	{
		j = 0;
		while (m_d->file[i][j])
		{
			if (m_d->file[i][j] != ' ' && m_d->file[i][j] != '\n' && 
				m_d->file[i][j] != '1' && m_d->file[i][j] != '0' && 
				m_d->file[i][j] != 'N')
				return (0);
			else if (m_d->file[i][j] == '\n')
				count_a++;
			else if (m_d->file[i][j] == '1' || m_d->file[i][j] == '0')
				count_b++;
			j++;
		}
		if (count_a >= 0 && count_b > 0)
			return (i);
		i++;
	}
	return (0);
}

int	ft_len(char **mini_map)
{
	int	len;
	int	longest;
	int	i;

	longest = 0;
	i = 0;
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
	return (longest);
}
