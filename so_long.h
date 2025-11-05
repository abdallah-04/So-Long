/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:16:25 by amufleh           #+#    #+#             */
/*   Updated: 2025/11/05 10:10:14 by amufleh          ###   ########.fr       */
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

int	is_in(char c);
int	is_CEP(char **map);
int	is_one_CEP(char **map);
void	find_player(char **map, int *p_x, int *p_y);
void	flood_fill(char **map, int x, int y);
int	check_topAbutton(char **map, int line);
int	check_leftAright(char **map, int line);
int	check_wh(char **map);
int	is_valid(char **map,int line);
char	**fill_map(char *path, int lines);
int	check_path(char *path);
#endif
