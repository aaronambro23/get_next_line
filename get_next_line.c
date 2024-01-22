/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaambros <aaambros@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:20:43 by aaambros          #+#    #+#             */
/*   Updated: 2024/01/22 12:19:16 by aaambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_data_from_file(int fd, char *buffer, char *backup_data)
{
	int		bytes_read;
	char	*temp_buff;

	bytes_read = 1;
	while (bytes_read != '\0')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(backup_data);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!backup_data)
			backup_data = ft_strdup("");
		temp_buff = ft_strjoin(backup_data, buffer);
		if (backup_data)
			free(backup_data);
		backup_data = temp_buff;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (backup_data);
}

static char	*extract_line_from_data(char *data)
{
	size_t	char_count;
	char	*temp_data;

	char_count = 0;
	while (data[char_count] != '\n' && data[char_count] != '\0')
		char_count++;
	if (data[char_count] == '\0' || data[1] == '\0')
		return (0);
	temp_data = ft_substr(data, char_count + 1, ft_strlen(data) - char_count);
	if (*temp_data == '\0')
	{
		free(temp_data);
		temp_data = NULL;
	}
	data[char_count + 1] = '\0';
	return (temp_data);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backup_data;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024 || read(fd, 0, 0) < 0
		|| fd == 1 || fd == 2)
	{
		free(buffer);
		free(backup_data);
		buffer = NULL;
		backup_data = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = read_data_from_file(fd, buffer, backup_data);
	free(buffer);
	if (!line)
	{
		free(backup_data);
		return (NULL);
	}
	backup_data = extract_line_from_data(line);
	return (line);
}
