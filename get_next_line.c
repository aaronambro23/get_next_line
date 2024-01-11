/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaambros <aaambros@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 16:20:43 by aaambros          #+#    #+#             */
/*   Updated: 2024/01/11 15:18:11 by aaambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_file_into_buffer(int fd, char *buf, char *backup)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line != '\0')
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
		{
			free(backup);
			return (NULL);
		}
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = ft_strjoin(backup, buf);
		if (backup)
			free(backup);
		backup = temp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*extract_line_from_buffer(char *line)
{
	size_t	count;
	char	*temp;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	temp = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (*temp == '\0')
	{
		free(temp);
		temp = NULL;
	}
	line[count + 1] = '\0';
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024 || read(fd, 0, 0) < 0
		|| fd == 1 || fd == 2)
	{
		free(buf);
		free(backup);
		buf = NULL;
		backup = NULL;
		return (NULL);
	}
	if (!buf)
		return (NULL);
	line = read_file_into_buffer(fd, buf, backup);
	free(buf);
	if (!line)
	{
		free(backup);
		return (NULL);
	}
	backup = extract_line_from_buffer(line);
	return (line);
}
