/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_boundaries.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 11:12:07 by amufleh           #+#    #+#             */
/*   Updated: 2025/12/02 15:38:24 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_topbutton(char **map, int line)
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

int	check_leftright(char **map, int line)
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

int	check_len(char **map)
{
	int	i;
	int	len;
	int	temp;

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

