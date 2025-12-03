/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:06:23 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/03 11:21:03 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <X11/keysym.h>

static int	render_next_frame(t_game *game)
{
	if (!game)
		return (0);
	mlx_clear_window(game->mlx, game->mlx_win);
	fill_image_map(game, 52);
	return (0);
}

static int	handle_key(int keycode, t_game *game)
{
	int	flag;
	int static	moves = 0;

	if (!game)
		return (0);
	flag = 0;
	moves++;
	if (keycode == KEY_ESC)
		destroy_win(game);
	else if (keycode == KEY_W)
		flag = move_player(game, game->player->x_axis - 1,
				game->player->y_axis);
	else if (keycode == KEY_S)
		flag = move_player(game, game->player->x_axis + 1,
				game->player->y_axis);
	else if (keycode == KEY_A)
		flag = move_player(game, game->player->x_axis,
				game->player->y_axis - 1);
	else if (keycode == KEY_D)
		flag = move_player(game, game->player->x_axis,
				game->player->y_axis + 1);
	if (flag)
		destroy_win(game);
 	put_num (moves);
	return (0);
}

static int setup_map(char *path, t_game *game)
{
	int	lines;
	char **temp;

	if (!game)
		return (0);
	lines = 0;
	if (!check_path(path))
		return (0);
	lines = count_line(path);
	temp = fill_map(path, lines);
	if (!is_valid(temp, lines))
	{
		free_map(game->map);
		free_map(temp);
		return (0);
	}
	free_map(temp);
	game->map = fill_map(path,lines);
	if (!game->map)
		{
			free_map(game->map);
			return (0);
		}
	game->c_num = count_c(game->map);
	return (1);
}

static int	setup_win(char *path,t_game *game)
{
	int	rows;
	int	cols;

	if (!path || !game)
		return (0);
	rows = count_line (path);
	cols = ft_strlen (game->map[0]) - 1;
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		destroy_win(game);
		return (0);
	}
	game->mlx_win = mlx_new_window(game->mlx, cols * 52, rows * 52, "so_long");
	if (!game->mlx_win)
	{
		destroy_win(game);
		return (0);
	}
	 // youuuuuu must check if fill image returns 0
	if (!fill_image(game))
		return(destroy_win(game));
	find_player(game->map, &game->player->x_axis, &game->player->y_axis);
	fill_image_map(game, 52);
	return (1);
}

int main(int args, char *argv[])
{
	//cc *.c get_next_line/getnextline.a -lmlx -lXext -lX11
	if (args != 2)
	{
		put_str("Error:\n!valid input");
		return (0);
	}
	t_textures	textures;
	t_player	player;
	t_game	game;

	game.player = &player;
	game.textures = &textures;
	game.map = NULL;
	if (!setup_map(argv[1], &game))
	{
		put_str("Error: !valid map\n");
		return (0);
	}
	if (!setup_win(argv[1], &game))
	{
		put_str("Error:\nWindow setup failed\n");
		return (0);
	}
	//mlx_key_hook(game.mlx_win, handle_key, &game);
	mlx_hook(game.mlx_win, 2, 1L<<0, handle_key, &game);
	//mlx_hook(game.mlx_win, 1, 1L<<0, handle_key, &game);
	mlx_loop_hook(game.mlx, render_next_frame, &game);
	mlx_loop(game.mlx);

	return (0);
}
