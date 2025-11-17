/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:03:26 by amufleh           #+#    #+#             */
/*   Updated: 2025/11/17 13:42:31 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <X11/keysym.h>

int is_there_c(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
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

int move_player(t_game *game, char m)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x_axis;
	new_y = game->player->y_axis;
	if (m == 'w')
		new_x-= 1;
	else if (m == 's')
		new_x += 1;
	else if (m == 'a')
		new_y -= 1;
	else if (m == 'd')
		new_y += 1;
	if (game->map[new_x][new_y] == '1')
		return (0);
	if (game->map[new_x][new_y] == 'C')
		game->map[new_x][new_y] = '0';
	if (game->map[new_x][new_y] == 'E')
	{
		if (!is_there_c(game->map))
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
		flag = move_player(game, 'w');
	else if (keycode == KEY_S)
		flag = move_player(game, 's');
	else if (keycode == KEY_A)
		flag = move_player(game, 'a');
	else if (keycode == KEY_D)
		flag = move_player(game, 'd');
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

int main()
{
    //cc *.c get_next_line/getnextline.a -lmlx -lXext -lX11
    char *path;
    char **temp;
    t_textures textures;
    t_player player;
    t_game game;
    int rows;
    int cols;
    int lines;


    path = "test.ber";
    if (!check_path(path))
    {
        printf("Error\nThe path is !valid\n");
        return (0);
    }
    lines = count_line(path);
    game.map = fill_map(path,lines);
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
    mlx_key_hook(game.mlx_win, handle_key, &game);
    //mlx_mouse_hook(game.mlx_win, mouse_hook, &vars);
    mlx_loop_hook(game.mlx, render_next_frame, &game);
    mlx_loop(game.mlx);

    return (0);
}
