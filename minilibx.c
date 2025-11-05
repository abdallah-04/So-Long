#include "so_long.h"
#include "mlx.h"
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
    char	*path = "/home/amufleh/Documents/core/So-Long/test_image.png";
	int		img_width = 1920;
	int		img_height = 1200;
    mlx = mlx_init();
    mlx_win = mlx_new_window (mlx, 1920, 1200, "test");
    img = mlx_xpm_file_to_image(mlx, path, &img_width, &img_height);
    mlx_put_image_to_window(mlx, mlx_win, img, 100, 333);
    mlx_loop(mlx);

    return 0;
}


