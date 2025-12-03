/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:16:25 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/03 17:12:20 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307

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
    char **map;
    int c_num;
    t_textures *textures;
    t_player *player;
}   t_game;

int	is_cep(char **map);
int	is_one_cep(char **map);
void	find_player(char **map, int *p_x, int *p_y);
void	flood_fill(char **map, int x, int y);
int	check_topbutton(char **map, int line);
int	check_leftright(char **map, int line);
int	check_len(char **map);
int	is_valid(char **map,int line);
char	**fill_map(char *path, int lines);
int	check_path(char *path);
int count_c(char **map);
int count_line(char *path);
void fill_image_map(t_game *game, int size);
int move_player(t_game *game, int new_x, int new_y);
int fill_image(t_game *game);
int free_map(char **map);
void    put_zero(t_game *game, int i, int j, int size);
void	put_player(t_game *game, int i, int j, int size);
void	put_collectible(t_game *game, int i, int j, int size);
void	put_wall(t_game *game, int i, int j, int size);
void	put_exit(t_game *game, int i, int j, int size);
int put_str(char *str);
void	put_num(int *n);
void	print_num(int n);
int destroy_img(t_game *game);
int destroy_win(t_game *game , int flag1, int flag2);
int	free_simag(t_game *game);

#endif
