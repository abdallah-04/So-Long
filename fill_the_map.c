/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:40:56 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/04 11:09:46 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_path(char *path)
{
	int		i;
	int		j;
	char	*target;

	target = ".ber\0";
	i = 0;
	while (path[i])
		i++;
	if (i < 4)
		return (0);
	j = 0;
	while (target[j])
	{
		if (path[i - 4 + j] != target[j])
			return (0);
		j++;
	}
	return (1);
}

char	**fill_map(char *path, int lines)
{
	char	**map;
	char	*str;
	int		i;
	int		fd;

	if (!path || !lines)
		return (NULL);
	i = 0;
	map = malloc((lines + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	str = get_next_line(fd);
	while (str)
	{
		map[i++] = str;
		str = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

int	count_line(char *path)
{
	char	*str;
	int		line;
	int		fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	line = 0;
	str = get_next_line(fd);
	while (str)
	{
		line++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (line);
}
