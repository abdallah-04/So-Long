#include "so_long.h"
#include <stdlib.h>
#include <X11/keysym.h>


typedef struct s_player
{
    int x_axis;
    int y_axis;
} t_player;

typedef struct s_textures
{
    void *wall;
    void *space1;
    void *space2;
    void *collectible;
    void *exit;
    void *player;
} t_textures;

// int handle_key(int keycode, t_textures *map)
// {
//     int move = 52;

//     if (keycode == XK_Escape)
//         exit(0);

//     if (keycode == XK_W)
//         map->player->y_axis -= move;
//     else if (keycode == XK_S)
//         map->player->y_axis += move;
//     else if (keycode == XK_A)
//         map->player->x_axis -= move;
//     else if (keycode == XK_D)
//         map->player->x_axis += move;

//     return 0;
// }
void fill_space(void *mlx, void* mlx_win, t_textures *ma, int size, char *map[])
{
    int i;
    int j;
    int x = 8;

    i = 0;
    while (x--)
    {
        j = 0;
        while (map[i][j] && map[i][j] != '\n')
        {

            if ((i + j) % 2 == 0)
                mlx_put_image_to_window(mlx, mlx_win, ma->space1, j * size, i * size);
            else
                mlx_put_image_to_window(mlx, mlx_win, ma->space2, j * size, i * size);
            j++;
        }
        i++;
    }
}

int main(void)
{
    char *map[] = {
        "111111111111\n\0",
        "1P0000C000E1\n\0",
        "101111011111\n\0",
        "100100000001\n\0",
        "111101111101\n\0",
        "1C0001000001\n\0",
        "101111101C01\n\0",
        "111111111111\0"
    };
    
    int rows = 8;    
    int cols = 12;   
    void *mlx;
    void *mlx_win;
    t_textures ma;
    int size = 52;
    int width ;
    int height;

    mlx = mlx_init();
    if (!mlx)
        return 1;

    mlx_win = mlx_new_window(mlx, rows * size, cols * size, "so_long");

    ma.wall = mlx_xpm_file_to_image(mlx, "textures/wall.xpm", &width, &height);
    ma.space1 = mlx_xpm_file_to_image(mlx, "textures/space1.xpm", &width, &height);
    ma.space2 = mlx_xpm_file_to_image(mlx, "textures/space2.xpm", &width, &height);
    ma.collectible = mlx_xpm_file_to_image(mlx, "textures/collectible.xpm", &width, &height);
    ma.exit = mlx_xpm_file_to_image(mlx, "textures/exit.xpm", &width, &height);
    ma.player = mlx_xpm_file_to_image(mlx, "textures/player.xpm", &width, &height);

    if (!ma.wall || !ma.space1 || !ma.space2 || !ma.collectible || !ma.exit) 
    {
        write(2, "Failed to load image\n", 21);
        return 1;
    }

    fill_space(mlx, mlx_win, &ma, size, map);
    mlx_put_image_to_window(mlx, mlx_win, ma.collectible, 4*size, 4 * size);


    mlx_loop(mlx);

    return 0;
}


