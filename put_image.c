/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:15:17 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/03 17:20:52 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_zero(t_game *game, int i, int j, int size)
{
	if ((i + j) % 2 == 0)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->textures->space1, j * size, i * size);
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->textures->space2, j * size, i * size);
}

void	put_player(t_game *game, int i, int j, int size)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->player->image, j * size, i * size);
}

void	put_collectible(t_game *game, int i, int j, int size)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->textures->collectible, j * size, i * size);
}

void	put_wall(t_game *game, int i, int j, int size)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->textures->wall, j * size, i * size);
}

void	put_exit(t_game *game, int i, int j, int size)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->textures->exit, j * size, i * size);
}
