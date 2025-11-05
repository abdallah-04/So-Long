/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:11:55 by amufleh           #+#    #+#             */
/*   Updated: 2025/11/05 11:35:56 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_cep(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' &&
				map[i][j] != 'C' && map[i][j] != 'P' &&
				map[i][j] != 'E' && map[i][j] != '\n')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	is_one_cep(char **map)
{
	int			j;
	int			i;
	static int	arr[3] = {0, 0, 0};

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				arr[0]++;
			else if (map[i][j] == 'E')
				arr[1]++;
			else if (map[i][j] == 'P')
				arr[2]++;
			j++;
		}
		i++;
	}
	if (arr[0] < 1 || arr[1] != 1 || arr[2] != 1)
		return (0);
	return (is_cep(map));
}

void	find_player(char **map, int *p_x, int *p_y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*p_x = i;
				*p_y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(char **map, int x, int y)
{
	int	len;

	if (x < 0 || !map[x])
		return ;
	len = ft_strlen(map[x]);
	if (y < 0 || y >= len)
		return ;
	if (map[x][y] == '1' || map[x][y] == '$' || map[x][y] == '\n')
		return ;
	map[x][y] = '$';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

int	is_valid(char **map, int line)
{
	int	i;
	int	j;
	int	p_x;
	int	p_y;

	i = 0;
	if (!map || !is_one_cep(map) || !check_topbutton(map, line)
		|| !check_leftright(map, line) || !check_len(map))
		return (0);
	find_player(map, &p_x, &p_y);
	flood_fill(map, p_x, p_y);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0' || map[i][j] == 'C' || map[i][j] == 'E')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
// int main(void)
// {
// 	char *str;
// 	char **map;
// 	char **temp;
// 	int line;
// 	int fd;
// 	char path[256];
// 	for (int i = 24; i > 0; i--)
// 	{
// 		sprintf(path, "maps/%d.ber", i);

// 		if (!check_path(path))
// 		{
// 			printf("error txt -> %d\n", i);
// 			continue;
// 		}
// 		fd = open(path, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror("open");
// 			continue;
// 		}
// 		line = 0;
// 		while ((str = get_next_line(fd)) != NULL)
// 		{
// 			line++;
// 			free(str);
// 		}
// 		close(fd);
// 		map = fill_map(path, line);
// 		temp = fill_map(path, line);
// 		for (int v = 0; map[v]; v++)
// 		{
// 			printf("%s", map[v]);
// 		}
// 		printf("\n");
// 		if (!is_valid(temp, line))
// 		{
// 			printf("\nerror -> %d\n", i);
// 			printf("--------------------------------\n");
// 			continue;
// 		}
// 		printf("\nnot error -> %d\n", i);
// 		printf("--------------------------------\n");
// 		// for (int j = 0; map[j]; j++)
// 		// {
// 		// 	printf("%s", map[j]);
// 		// 	free(map[j]);
// 		// 	free(temp[j]);
// 		// }
// 		free(map);
// 		free(temp);
// 	}
// 	return 0;
// }
