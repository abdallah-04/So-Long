/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:40:56 by amufleh           #+#    #+#             */
/*   Updated: 2025/11/10 15:47:03 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**fill_map(char *path, int lines)
{
	char	**map;
	char	*str;
	int		i;
	int		fd;

	if (!path)
		return (0);
	i = 0;
	map = malloc((lines + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while ((str = get_next_line(fd)) != NULL)
		map[i++] = str;
	map[i] = NULL;
	close(fd);
	return (map);
}
int	check_path(char *path)
{
	int		i;
	int		j;
	char	*target;


	target = ".ber";
	if (!path)
		return (0);
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
