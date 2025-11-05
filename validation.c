#include "so_long.h"

int	is_in(char c)
{
	int	i;
	char	*str;

	str = "01CPE\n";
	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}
int	is_CEP(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '\n' && !is_in(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
int	is_one_CEP(char **map)
{
	int arr[3] = {0, 0, 0};
	int	i;
	int	j;

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
	return (is_CEP(map));
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
int	check_topAbutton(char **map, int line)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(map[0]);
	if (map[0][len - 1] == '\n')
		len--;
	while (i < len)
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	len = ft_strlen(map[line - 1]);
	if (map[line - 1][len - 1] == '\n')
		len--;
	while (i < len)
	{
		if (map[line - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_leftAright(char **map, int line)
{
	int	i;
	int	len;

	i = 0;
	while (i < line)
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			len--;
		if (map[i][0] != '1' || map[i][len - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_wh(char **map)
{
	int	i;
	int	len;
	int	temp;

	if (!map || !map[0])
		return (0);
	len = ft_strlen(map[0]);
	if (map[0][len - 1] == '\n')
		len--;
	i = 1;
	while (map[i])
	{
		temp = ft_strlen(map[i]);
		if (map[i][temp - 1] == '\n')
			temp--;
		if (temp != len)
			return (0);
		i++;
	}
	return (1);
}
int	is_valid(char **map,int line)
{
	int	i;
	int	j;
	int	p_x;
	int	p_y;

	i = 0;
	if (!map || !is_one_CEP(map) || !check_topAbutton(map, line)
		|| !check_leftAright(map, line) || !check_wh(map))
		return (0);
	find_player(map, &p_x, &p_y);
	flood_fill(map, p_x, p_y);
	for (int x = 0; map[x]; x++)
	{
		printf("%s", map[x]);
	}
	printf("\n");
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
char	**fill_map(char *path, int lines)
{
	char	**map;
	char	*str;
	int		i;
	int		fd;

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
int main()
{
	char *str;
	char **map;
	char **temp;
	int line;
	int fd;
	char *path;
	path = "test.ber";
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
	}
		line = 0;
		while ((str = get_next_line(fd)) != NULL)
		{
			line++;
			free(str);
		}
		close(fd);
		map = fill_map(path, line);
		temp = fill_map(path, line);
		for (int v = 0; map[v]; v++)
		{
			printf("%s", map[v]);
		}
		printf("\n");
		if (!is_valid(temp, line))
		{
			printf("\nerror ->\n");
			printf("--------------------------------\n");
		}
		else
		{
			printf("\nnot error ->\n");
			printf("--------------------------------\n");
		}
		for (int j = 0; map[j]; j++)
		{
			printf("%s", map[j]);
			free(map[j]);
			free(temp[j]);
		}
		free(map);
		free(temp);
	return 0;
}
