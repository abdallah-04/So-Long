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
	static int arr[3] = {0, 0, 0};
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
	if (x < 0 || y < 0 || !map[x] || !map[x][y])
		return ;
	if (map[x][y] == '1' || map[x][y] == '$' || map[x][y] == '\n')
		return ;
	map[x][y] = '$';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}
int	is_valid(char **map)
{
	int	i;
	int	j;
	int	p_x;
	int	p_y;

	i = 0;
	if (!is_one_CEP (map))
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
char	**fill_map(int lines)
{
	char	**map;
	char	*str;
	int	i;
	int	fd;

	i = 0;
	map = malloc((lines + 1) * sizeof(char *));
	if (!map)
		return NULL;
	fd = open("text.txt", O_RDONLY);
	while ((str = get_next_line(fd)) != NULL)
	{
		map[i++] = str;
	}
	map[i] = NULL;
	close (fd);
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
int	main(void)
{
	char *str;
	char **map;
	char **temp;
	int line = 0;
	int fd;
	char *path;

	path = "text.ber";
	if (!check_path(path))
		printf("error");
	fd = open(path, O_RDONLY);
	while ((str = get_next_line(fd)) != NULL)
	{
		line++;
		free(str);
	}
	close(fd);
	map = fill_map(line);
	temp = fill_map(line);
	printf("%d\n",is_valid(temp));
	for (int i = 0; map[i]; i++)
	{
		printf("%s", map[i]);
		free(map[i]);
	}
	free(map);
	return 0;
}
