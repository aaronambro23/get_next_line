/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaambros <aaambros@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:38:41 by aaambros          #+#    #+#             */
/*   Updated: 2024/01/09 13:41:03 by aaambros         ###   ########.fr       */
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
			backup = NULL;
			return (0);
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
	return (temp);
}

static char	*extract_line_from_backup(char *backup)
{
	size_t	count;
	char	*temp;

	count = 0;
	while (backup[count] != '\n' && backup[count] != '\0')
		count++;
	temp = ft_substr(backup, 0, count + 1);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free(backup);
		backup = NULL;
		return (0);
	}
	backup = read_file_into_buffer(fd, buf, backup);
	free(buf);
	if (!backup)
		return (0);
	line = extract_line_from_backup(backup);
	buf = extract_line_from_buffer(backup);
	free(backup);
	backup = buf;
	return (line);
}
