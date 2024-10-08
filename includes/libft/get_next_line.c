/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lo <lo@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:52:17 by elmaleuv          #+#    #+#             */
/*   Updated: 2023/02/03 11:44:13 by lo               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *storage)
{
	int		i;
	char	*line_to_return;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line_to_return = malloc(sizeof(char) * (i + 2));
	if (!line_to_return)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line_to_return[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		line_to_return[i] = storage[i];
		i++;
	}
	line_to_return[i] = '\0';
	return (line_to_return);
}

char	*save_line(char *storage)
{
	int		i;
	int		j;
	char	*line_to_save;

	i = 0;
	j = 0;
	while (storage && storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		i++;
	line_to_save = malloc(sizeof(char) * (ft_strlen_gnl(storage) - i) + 1);
	if (!line_to_save)
		return (NULL);
	while (storage && storage[i])
		line_to_save[j++] = storage[i++];
	line_to_save[j] = '\0';
	free(storage);
	if (line_to_save[0] == '\0')
	{
		free(line_to_save);
		return (NULL);
	}
	return (line_to_save);
}

char	*line_reader(int fd, char *storage)
{
	int		cursor;
	char	*tmp;

	tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	cursor = 1;
	while (!find_the_n(storage) && cursor != 0)
	{
		cursor = read(fd, tmp, BUFFER_SIZE);
		if (cursor == -1)
		{
			free(tmp);
			return (NULL);
		}
		tmp[cursor] = '\0';
		storage = ft_strjoin_gnl(storage, tmp);
	}
	free(tmp);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage[fd] = line_reader(fd, storage[fd]);
	if (!storage[fd] || storage[fd][0] == '\0')
	{
		if (storage[fd] && storage[fd][0] == '\0')
		{
			free(storage[fd]);
			storage[fd] = NULL;
		}
		return (NULL);
	}
	line = get_line(storage[fd]);
	if (!line)
	{
		free(storage[fd]);
		return (NULL);
	}
	storage[fd] = save_line(storage[fd]);
	return (line);
}
