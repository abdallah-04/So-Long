/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:35:39 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/03 17:19:27 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (0);
}

void	put_num(int *n)
{
	*n = *n + 1;
	print_num(*n);
	write(1, "\n", 1);
}

void	print_num(int n)
{
	char c;

	if (n >= 10)
		print_num(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
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

