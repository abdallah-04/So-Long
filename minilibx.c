/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:03:26 by amufleh           #+#    #+#             */
/*   Updated: 2026/01/23 15:06:36 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill_image_map(t_game *game, int size)
{
	int	i;
	int	j;

	i = 0;
	if (!game -> map)
		return ;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			if (game->map[i][j] == '0' || game->map[i][j] == 'P')
				put_zero (game, i, j, size);
			if (game->map[i][j] == 'C')
				put_collectible (game, i, j, size);
			if (game->map[i][j] == '1')
				put_wall (game, i, j, size);
			if (game->map[i][j] == 'E')
				put_exit (game, i, j, size);
			j++;
		}
		i++;
	}
	put_player (game, game->player->x_axis,
		game->player->y_axis, size);
}

int	move_player(t_game *game, int new_x, int new_y)
{
	static int	count;
	int			flag;

	if (!game->map)
		return (0);
	flag = 0;
	if (game->map[new_x][new_y] == '1')
		return (2);
	if (game->map[new_x][new_y] == 'C')
	{
		count++;
		game->map[new_x][new_y] = '0';
	}
	if (game->map[new_x][new_y] == 'E')
	{
		if (count == game->c_num)
			return (1);
	}
	game->player->x_axis = new_x;
	game->player->y_axis = new_y;
	render_next_frame(game);
	return (0);
}

int	fill_image(t_game *game)
{
	int	width;
	int	height;

	if (! game)
		return (0);
	game->textures->wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall3.xpm", &width, &height);
	game->textures->space1 = mlx_xpm_file_to_image(game->mlx,
			"textures/space1.xpm", &width, &height);
	game->textures->space2 = mlx_xpm_file_to_image(game->mlx,
			"textures/space2.xpm", &width, &height);
	game->textures->collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/collectible2_b.xpm", &width, &height);
	game->textures->exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit2.xpm", &width, &height);
	game->player->image = mlx_xpm_file_to_image(game->mlx,
			"textures/player2.xpm", &width, &height);
	if (!game->textures->wall || !game->textures->space1
		|| !game->textures->space2 || !game->textures->collectible
		|| !game->textures->exit || !game->player->image)
		return (free_simag(game));
	return (1);
}

int	free_simag(t_game *game)
{
	if (game->textures->wall)
		mlx_destroy_image(game->mlx, game->textures->wall);
	if (game->textures->collectible)
		mlx_destroy_image(game->mlx, game->textures->collectible);
	if (game->textures->exit)
		mlx_destroy_image(game->mlx, game->textures->exit);
	if (game->textures->space1)
		mlx_destroy_image(game->mlx, game->textures->space1);
	if (game->textures->space1)
		mlx_destroy_image(game->mlx, game->textures->space2);
	if (game->player->image)
		mlx_destroy_image(game->mlx, game->player->image);
	destroy_win(game, 0, 1);
	return (0);
}
//so_long
