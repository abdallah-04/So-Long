/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:35:39 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/03 15:14:22 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void put_num(int n)
{
	char c;

	if (n >= 10)
		put_num(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
	if (n < 10)
		write(1, "\n", 1);
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

int	destroy_img(t_game *game)
{
	mlx_destroy_image(game->mlx, game->textures->collectible);
	mlx_destroy_image(game->mlx, game->textures->wall);
	mlx_destroy_image(game->mlx, game->player->image);
	mlx_destroy_image(game->mlx, game->textures->exit);
	mlx_destroy_image(game->mlx, game->textures->space1);
	mlx_destroy_image(game->mlx, game->textures->space2);
	return (0);
}

int destroy_win(t_game *game , int flag1, int flag2)
{
	 if (flag1)
	 {
		destroy_img(game);
	 }
	 if (flag2)
	 {
		mlx_destroy_window(game->mlx, game->mlx_win);
	 }
	free_map(game->map);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}

