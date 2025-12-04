/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:16:25 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/04 12:30:23 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_player
{
	int		x_axis;
	int		y_axis;
	void	*image;
}	t_player;

typedef struct s_textures
{
	void	*wall;
	void	*space1;
	void	*space2;
	void	*collectible;
	void	*exit;
}	t_textures;

typedef struct s_game
{
	t_textures	*textures;
	t_player	*player;
	void		*mlx;
	void		*mlx_win;
	char		**map;
	int			c_num;
}	t_game;

int		is_cep(char **map);
int		is_one_cep(char **map);
int		check_topbutton(char **map, int line);
int		check_leftright(char **map, int line);
int		check_len(char **map);
int		is_valid(char **map, int line);
int		check_path(char *path);
int		count_c(char **map);
int		count_line(char *path);
int		move_player(t_game *game, int new_x, int new_y);
int		fill_image(t_game *game);
int		free_map(char **map);
int		put_str(char *str);
int		destroy_img(t_game *game);
int		destroy_win(t_game *game, int flag1, int flag2);
int		free_simag(t_game *game);
int		close_win(t_game *game);
int		render_next_frame(t_game *game);
int		handle_key(int keycode, t_game *game);
int		setup_map(char *path, t_game *game);
int		setup_win(char *path, t_game *game);
char	**fill_map(char *path, int lines);
void	find_player(char **map, int *p_x, int *p_y);
void	flood_fill(char **map, int x, int y);
void	put_num(int *n);
void	print_num(int n);
void	put_zero(t_game *game, int i, int j, int size);
void	put_player(t_game *game, int i, int j, int size);
void	put_collectible(t_game *game, int i, int j, int size);
void	put_wall(t_game *game, int i, int j, int size);
void	put_exit(t_game *game, int i, int j, int size);
void	fill_image_map(t_game *game, int size);
#endif
