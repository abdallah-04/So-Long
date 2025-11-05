/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:06:23 by amufleh           #+#    #+#             */
/*   Updated: 2025/11/05 13:04:31 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int main()
// {
// 	char *str;
// 	char **map;
// 	char **temp;
// 	int line;
// 	int fd;
// 	char *path;
// 	path = "test.ber";
// 	fd = open(path, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 	}
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
// 			printf("\nerror ->\n");
// 			printf("--------------------------------\n");
// 		}
// 		else
// 		{
// 			printf("\nnot error ->\n");
// 			printf("--------------------------------\n");
// 		}
// 		for (int j = 0; map[j]; j++)
// 		{
// 			printf("%s", map[j]);
// 			free(map[j]);
// 			free(temp[j]);
// 		}
// 		free(map);
// 		free(temp);
// 	return 0;
// }
