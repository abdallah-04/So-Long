/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:35:39 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/02 16:05:05 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void put_num(int n)
{
    char c;

    if (n >= 10)
        put_num(n / 10);

    c = (n % 10) + '0';
    write(1, &c, 1);

    if (n < 10) // print newline only once
        write(1, "\n", 1);
}




void free_map(char **map)
{
	int	i;

	if (!map || !map[0])
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
