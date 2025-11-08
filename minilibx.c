/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:03:26 by amufleh           #+#    #+#             */
/*   Updated: 2025/11/08 15:10:15 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <X11/keysym.h>


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
    t_player *player;
} t_textures;

typedef struct s_game
{
    void *mlx;
    void *mlx_win;
    t_textures *textures;
}   t_game;

int handle_key(int keycode, t_textures *map)
{
    int move = 52;

    if (keycode == XK_Escape)
        exit(0);
    if (keycode == XK_W)
        map->player->y_axis -= move;
    if (keycode == XK_S)
        map->player->y_axis += move;
    if (keycode == XK_A)
        map->player->x_axis -= move;
    if (keycode == XK_D)
        map->player->x_axis += move;

    return 0;
}
void fill_space(void *mlx, void* mlx_win, t_textures *ma, int size, char *map[])
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j] && map[i][j] != '\n')
        {
            if ((i + j) % 2 == 0)
                mlx_put_image_to_window(mlx, mlx_win, ma->space1, i * size, j * size);
            else
                mlx_put_image_to_window(mlx, mlx_win, ma->space2, i * size, j * size);
            j++;
        }
        i++;
    }
}
void fill_collectible_player(void *mlx, void* mlx_win, t_textures *ma, int size, char *map[])
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j] && map[i][j] != '\n')
        {
            if (map[i][j] == 'P')
                mlx_put_image_to_window(mlx, mlx_win, ma->player->image, i * size, j * size);
            if (map[i][j] == 'C')
                mlx_put_image_to_window(mlx, mlx_win, ma->collectible, i * size, j * size);
            if (map[i][j] == '1')
                mlx_put_image_to_window(mlx, mlx_win, ma->wall, i * size, j * size);
            if (map[i][j] == 'E')
                mlx_put_image_to_window(mlx, mlx_win, ma->exit, i * size, j * size);
            j++;
        }
        i++;
    }

}


int render_next_frame(t_game *game)
{
    mlx_clear_window(game->mlx, game->mlx_win);
    mlx_put_image_to_window(game->mlx,game->mlx_win,game->textures->player->image,game->textures->player->x_axis * 52,game->textures->player->y_axis * 52);

    return (0);
}
int main(void)
{
    char *map[] = {
        "1111111111111\n",
        "1P0000C000E01\n",
        "1011110111101\n",
        "1001000000001\n",
        "1111011111001\n",
        "1C00010000001\n",
        "101111101C001\n",
        "1111111111111\0",
        NULL
    };
    t_textures ma;
    t_player player;
    t_game game;
    int rows = 8;
    int cols = 13;
    int size = 52;
    int width;
    int height;

    game.mlx = mlx_init();
    if (!game.mlx)
        return (0);
    game.mlx_win = mlx_new_window(game.mlx, rows * size, cols * size, "so_long");
    ma.player = &player;
    game.textures = &ma;
    find_player(map, &player.x_axis, &player.y_axis);
    ma.wall = mlx_xpm_file_to_image(game.mlx, "textures/wall3.xpm", &width, &height);
    ma.space1 = mlx_xpm_file_to_image(game.mlx, "textures/space1.xpm", &width, &height);
    ma.space2 = mlx_xpm_file_to_image(game.mlx, "textures/space2.xpm", &width, &height);
    ma.collectible = mlx_xpm_file_to_image(game.mlx, "textures/collectible2_b.xpm", &width, &height);
    ma.exit = mlx_xpm_file_to_image(game.mlx, "textures/exit2.xpm", &width, &height);
    ma.player->image = mlx_xpm_file_to_image(game.mlx, "textures/player2.xpm", &width, &height);

    if (!ma.wall || !ma.space1 || !ma.space2 || !ma.collectible || !ma.exit || !ma.player->image)
    {
        write(2, "Failed to load image\n", 21);
        return (0);
    }
    fill_space(game.mlx, game.mlx_win, &ma, size, map);
    fill_collectible_player(game.mlx, game.mlx_win, &ma, size, map);
    mlx_key_hook(game.mlx_win, handle_key, &ma);
    //mlx_loop_hook(game.mlx, render_next_frame, &game);
    printf("%d",player.y_axis);
    mlx_loop(game.mlx);


    return (0);
}


