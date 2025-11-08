/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:03:26 by amufleh           #+#    #+#             */
/*   Updated: 2025/11/08 18:15:46 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <X11/keysym.h>


#define XK_W1 119
#define XK_A1 97
#define XK_S1 115
#define XK_D1 100
#define XK_Escape1 65307

typedef struct s_player
{
    int x_axis;
    int y_axis;
    void *image;
} t_player;

typedef struct s_textures
{
    void *wall;
    void *space1;
    void *space2;
    void *collectible;
    void *exit;
} t_textures;

typedef struct s_game
{
    void *mlx;
    void *mlx_win;
    t_textures *textures;
    t_player *player;
}   t_game;

int handle_key(int keycode, t_game *game)
{
    int move = 52;

    if (keycode == XK_Escape1)
        exit(0);
    if (keycode == XK_W1)
        game->player->y_axis -= move;
    if (keycode == XK_S1)
        game->player->y_axis += move;
    if (keycode == XK_A1)
        game->player->x_axis -= move;
    if (keycode == XK_D1)
        game->player->x_axis += move;

    return 0;
}
void fill_image_map(void *mlx, void* mlx_win, t_game *game, int size, char *map[])
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j] && map[i][j] != '\n')
        {
            if (map[i][j] == '0' && (i + j) % 2 == 0)
                mlx_put_image_to_window(mlx, mlx_win, game->textures->space1, i * size, j * size);
            if (map[i][j] == '0' && (i + j) % 2 != 0)
                mlx_put_image_to_window(mlx, mlx_win, game->textures->space2, i * size, j * size);
            if (map[i][j] == 'P')
                mlx_put_image_to_window(mlx, mlx_win, game->player->image, i * size, j * size);
            if (map[i][j] == 'C')
                mlx_put_image_to_window(mlx, mlx_win, game->textures->collectible, i * size, j * size);
            if (map[i][j] == '1')
                mlx_put_image_to_window(mlx, mlx_win, game->textures->wall, i * size, j * size);
            if (map[i][j] == 'E')
                mlx_put_image_to_window(mlx, mlx_win, game->textures->exit, i * size, j * size);
            j++;
        }
        i++;
    }
}
int fill_image(t_game *game)
{
    int width;
    int height;

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
    mlx_put_image_to_window(game->mlx,game->mlx_win,game->player->image,game->player->x_axis * 52,game->player->y_axis * 52);

    return (0);
}
int count_line(char *path)
{
    int line;
    int fd;
    char *str;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
	}
    line = 0;
	while ((str = get_next_line(fd)) != NULL)
	{
		line++;
		free(str);
	}
    close(fd);
    return (line);
}
// int main()
// {
//     char *path;
//     char **map;
//     char **temp;
//     t_textures ma;
//     t_player player;
//     t_game game;
//     int rows;
//     int cols;
//     int size;

//     size = 52;
//     path = "test.ber";
//     map = fill_map(path,count_line(path));
//     temp = fill_map(path, count_line(path));
// 	if (!is_valid(temp, count_line(path)))
//         printf("\nerror ->\n");
//     rows = count_line (path);
//     cols = ft_strlen (map[0]);
//     game.mlx = mlx_init();
//     if (!game.mlx)
//         return (0);
//     game.mlx_win = mlx_new_window(game.mlx, rows * size, cols * size, "so_long");
//     game.player = &player;
//     game.textures = &ma;
//     fill_image(&game);
//     find_player(map, &player.x_axis, &player.y_axis);
//     fill_image_map(game.mlx, game.mlx_win, &game, size, map);
//     mlx_key_hook(game.mlx_win, handle_key, &game);
//     //mlx_loop_hook(game.mlx, render_next_frame, &game);
//     printf("%d",player.y_axis);
//     for (int j = 0; map[j]; j++)
// 		printf("%s", map[j]);
//     mlx_loop(game.mlx);

//     return (0);
// }


