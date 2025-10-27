/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amufleh <amufleh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 09:01:01 by amufleh           #+#    #+#             */
/*   Updated: 2025/09/23 09:21:11 by amufleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(void *str)
{
	free(str);
	return (NULL);
}

char	*fill_words(int fd, char *words_read)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0)
	{
		if (ft_strchr(words_read, '\n'))
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(words_read);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		words_read = ft_strjoin(words_read, buffer);
	}
	free(buffer);
	return (words_read);
}

char	*write2endl(char *words_read)
{
	char	*line;
	int		i;

	if (!words_read || !*words_read)
		return (NULL);
	i = 0;
	while (words_read[i] && words_read[i] != '\n')
		i++;
	line = malloc(i + (words_read[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (words_read[i] && words_read[i] != '\n')
	{
		line[i] = words_read[i];
		i++;
	}
	if (words_read[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*final_words(char *words_read)
{
	char	*leftover;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!words_read)
		return (NULL);
	while (words_read[i] && words_read[i] != '\n')
		i++;
	if (!words_read[i])
		return (ft_free(words_read));
	i++;
	leftover = malloc(ft_strlen(words_read + i) + 1);
	if (!leftover)
		return (ft_free(words_read));
	while (words_read[i])
		leftover[j++] = words_read[i++];
	leftover[j] = '\0';
	free(words_read);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*words_read[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	words_read[fd] = fill_words(fd, words_read[fd]);
	if (!words_read[fd])
		return (NULL);
	line = write2endl(words_read[fd]);
	words_read[fd] = final_words(words_read[fd]);
	if (!line)
	{
		free(words_read[fd]);
		return (NULL);
	}
	return (line);
}
// int main()
// {
// 	int fd = open("text.txt", O_RDONLY | O_CREAT, 0644);
// 	char *line;
// 	while((line = get_next_line(fd)))
// 	{
// 		printf("%s",line);
// 		free(line);
// 	}
// 	close(fd);
// }
