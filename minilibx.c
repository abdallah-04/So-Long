/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:03:26 by amufleh           #+#    #+#             */
/*   Updated: 2025/11/17 18:16:30 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <X11/keysym.h>

int count_c(char **map)
{
	int	i;
	int	j;
	int count;

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

void fill_image_map(t_game *game, int size)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			if (game->map[i][j] == '0' && (i + j) % 2 == 0)
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures->space1, j * size, i * size);
			if (game->map[i][j] == '0' && (i + j) % 2 != 0)
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures->space2, j * size, i * size);
			if (game->map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->player->image, j * size, i * size);
			if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures->collectible, j * size, i * size);
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures->wall, j * size, i * size);
			if (game->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_win, game->textures->exit, j * size, i * size);
			j++;
		}
		i++;
	}
}

void swap_chars(char *c1, char *c2)
{
	char	temp;

	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

int move_player(t_game *game, int new_x, int new_y)
{
	char temp;
	int	static count = 0;

	temp = 'E';
	if (game->map[new_x][new_y] == '1')
		return (0);
	if (game->map[new_x][new_y] == 'C')
		{
			count++;
			game->map[new_x][new_y] = '0';
		}
	if (game->map[new_x][new_y] == 'E')
	{
		if (count == game->c_num)
			return (1);
		return (0);
	}
	swap_chars(&game->map[game->player->x_axis][game->player->y_axis], &game->map[new_x][new_y]);
	game->player->x_axis = new_x;
	game->player->y_axis = new_y;
	return (0);
}

int handle_key(int keycode, t_game *game)
{
	int	flag;
	int static moves = 0;

	flag = 0;
	moves++;
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W)
		flag = move_player(game, game->player->x_axis - 1, game->player->y_axis);
	else if (keycode == KEY_S)
		flag = move_player(game, game->player->x_axis + 1, game->player->y_axis);
	else if (keycode == KEY_A)
		flag = move_player(game, game->player->x_axis, game->player->y_axis - 1);
	else if (keycode == KEY_D)
		flag = move_player(game, game->player->x_axis, game->player->y_axis + 1);
	if (flag)
		exit(0);
 		printf("%d\n",moves);
	return (0);
}

int fill_image(t_game *game)
{
	int	width;
	int	height;

	if (! game)
		return (0);
	game->textures->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall3.xpm", &width, &height);
	game->textures->space1 = mlx_xpm_file_to_image(game->mlx, "textures/space1.xpm", &width, &height);
	game->textures->space2 = mlx_xpm_file_to_image(game->mlx, "textures/space2.xpm", &width, &height);
	game->textures->collectible = mlx_xpm_file_to_image(game->mlx, "textures/collectible2_b.xpm", &width, &height);
	game->textures->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit2.xpm", &width, &height);
	game->player->image = mlx_xpm_file_to_image(game->mlx, "textures/player2.xpm", &width, &height);
	if (!game->textures->wall || !game->textures->space1 || !game->textures->space2 ||
			!game->textures->collectible || !game->textures->exit || !game->player->image)
		return (0);
	return (1);
}

int render_next_frame(t_game *game)
{
	mlx_clear_window(game->mlx, game->mlx_win);
	fill_image_map(game, 52);
	return (0);
}
int count_line(char *path)
{
	int	line;
	int	fd;
	char	*str;

	if (! path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		perror("open");
	line = 0;
	while ((str = get_next_line(fd)) != NULL)
	{
		line++;
		free(str);
	}
	close(fd);
	return (line);
}

void free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int main(int args, char *argv[])
{
	//cc *.c get_next_line/getnextline.a -lmlx -lXext -lX11
	int	rows;
	int	cols;
	int	lines;
	char	*path;
	char	**temp;
	t_textures	textures;
	t_player	player;
	t_game	game;

	if (args != 2)
	{
		printf("Error\n!valid input");
		return (0);
	}
	path = argv[1];
	if (!check_path(path))
	{
		printf("Error\nThe path is !valid\n");
		return (0);
	}
	lines = count_line(path);
	game.map = fill_map(path,lines);
	game.c_num = count_c(game.map);
	temp = fill_map(path, lines);
	if (!is_valid(temp, lines))
	{
		free_map(game.map);
		free_map(temp);
		printf("Error\nThe map is !valid\n");
		return (0);
	}
	rows = count_line (path);
	cols = ft_strlen (game.map[0]) - 1;
	game.mlx = mlx_init();
	if (!game.mlx)
		return (0);
	game.mlx_win = mlx_new_window(game.mlx, cols * 52, rows * 52, "so_long");
	if (!game.mlx_win)
		return (0);
	game.player = &player;
	game.textures = &textures;
	fill_image(&game);
	find_player(game.map, &player.x_axis, &player.y_axis);
	fill_image_map(&game, 52);
	//mlx_key_hook(game.mlx_win, handle_key, &game);
	mlx_hook(game.mlx_win, 2, 1L<<0, handle_key, &game);
	//mlx_hook(game.mlx_win, 1, 1L<<0, handle_key, &game);
	mlx_loop_hook(game.mlx, render_next_frame, &game);
	mlx_loop(game.mlx);

	return (0);
}
