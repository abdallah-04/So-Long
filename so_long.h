/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:16:25 by amufleh           #+#    #+#             */
/*   Updated: 2025/11/17 18:12:28 by amufleh          ###   ########.fr       */
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

#endif
