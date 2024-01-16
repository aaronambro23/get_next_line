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


static char	*readDataFromFile(int fileDescriptor, char *buffer, char *backupData)
{
	int		bytesRead;
	char	*tempBuffer;

	bytesRead = 1;
	while (bytesRead != '\0')
	{
		bytesRead = read(fileDescriptor, buffer, BUFFER_SIZE);
		if (bytesRead == -1)
		{
			free(backupData);
			return (NULL);
		}
		else if (bytesRead == 0)
			break ;
		buffer[bytesRead] = '\0';
		if (!backupData)
			backupData = duplicateString("");
		tempBuffer = joinStrings(backupData, buffer);
		if (backupData)
			free(backupData);
		backupData = tempBuffer;
		if (findCharacter(buffer, '\n'))
			break ;
	}
	return (backupData);
}

static char	*extractLineFromData(char *data)
{
	size_t	characterCount;
	char	*tempData;

	characterCount = 0;
	while (data[characterCount] != '\n' && data[characterCount] != '\0')
		characterCount++;
	if (data[characterCount] == '\0' || data[1] == '\0')
		return (0);
	tempData = getSubstring(data, characterCount + 1, getStringLength(data) - characterCount);
	if (*tempData == '\0')
	{
		free(tempData);
		tempData = NULL;
	}
	data[characterCount + 1] = '\0';
	return (tempData);
}

char	*getNextLine(int fileDescriptor)
{
	char		*line;
	char		*buffer;
	static char	*backupData;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fileDescriptor < 0 || BUFFER_SIZE <= 0 || fileDescriptor >= 1024 || read(fileDescriptor, 0, 0) < 0
		|| fileDescriptor == 1 || fileDescriptor == 2)
	{
		free(buffer);
		free(backupData);
		buffer = NULL;
		backupData = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = readDataFromFile(fileDescriptor, buffer, backupData);
	free(buffer);
	if (!line)
	{
		free(backupData);
		return (NULL);
	}
	backupData = extractLineFromData(line);
	return (line);
}