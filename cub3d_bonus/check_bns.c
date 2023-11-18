/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:55:49 by ckannane          #+#    #+#             */
/*   Updated: 2023/11/18 13:05:20 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	bonus_component_check(t_bjt *m_d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (m_d->mini_map[i])
	{
		j = 0;
		while (m_d->mini_map[i][j])
		{
			if (m_d->mini_map[i][j] != '1' && m_d->mini_map[i][j] != '2' && 
				m_d->mini_map[i][j] != '0' && m_d->mini_map[i][j] != 'N' && 
				m_d->mini_map[i][j] != 'W' && m_d->mini_map[i][j] != 'S' && 
				m_d->mini_map[i][j] != 'E' && m_d->mini_map[i][j] != '\n' && 
				m_d->mini_map[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	check_all_b(t_bjt *map)
{
	if (!tab_check(map) || !border_check(map->mini_map) || 
		!borders_checker(map) || !one_check(map) || 
		!bonus_component_check(map) || player_checker(map->mini_map) != 1)
	{
		ft_free_struct(map);
		erroc_exit(map, "Numbers incorrects, Invalid map!");
	}
}
