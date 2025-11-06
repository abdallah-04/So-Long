#include "so_long.h"
#include <stdlib.h>
#include <X11/keysym.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define PLAYER_SIZE 50
#define PLAYER_COLOR 0x0000FF

typedef struct s_player
{
    int x_axis;
    int y_axis;
} t_player;

typedef struct s_textures
{
    void *wall;
    void *collect;
    void *exit;
    t_player *player;
} t_textures;
// int handle_key(int keycode, t_data *data)
// {
//     int move = 5;

//     if (keycode == XK_Escape)
//         exit(0);

//     if (keycode == XK_W)
//         data->player.y_axis -= move;
//     else if (keycode == XK_S)
//         data->player.y_axis += move;
//     else if (keycode == XK_A)
//         data->player.x_axis -= move;
//     else if (keycode == XK_D)
//         data->player.x_axis += move;

//     return 0;
// }
int main(void)
{
    void *mlx;
    void *mlx_win;
    void *img;
    int img_width;
    int img_height;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "so_long");
    img = mlx_xpm_file_to_image(mlx, "wall.xpm", &img_width, &img_height);
    if (!img)
    {
        write(2, "Failed to load image\n", 21);
        return (1);
    }
    mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);

    mlx_loop(mlx);
}


