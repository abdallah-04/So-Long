/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:11:54 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/03 18:13:31 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_c(char **map)
{
	int	i;
	int	j;
	int	count;

	if (!map || !map[0])
		return (0);
	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	free_map(char **map)
{
	int	i;

	if (!map || !map[0])
		return (0);
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (0);
}

int close_win(t_game *game)
{
	destroy_win(game, 1, 1);
	return (0);
}
