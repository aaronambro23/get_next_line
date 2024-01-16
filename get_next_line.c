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

static char	*readDataFromFile(int fd, char *buffer, char *backupData)
{
	int		bytesRead;
	char	*tempBuff;

	bytesRead = 1;
	while (bytesRead != '\0')
	{
		bytesRead = read(fd, buffer, BUFFER_SIZE);
		if (bytesRead == -1)
		{
			free(backupData);
			return (NULL);
		}
		else if (bytesRead == 0)
			break ;
		buf[bytesRead] = '\0';
		if (!backupData)
			backupData = ft_strdup("");
		tempBuff = ft_strjoin(backupData, buffer);
		if (backupData)
			free(backupData);
		backupData = tempBuff;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (backupData);
}

static char	*extractLineFromData(char *data)
{
	size_t	charCount;
	char	*tempData;

	charCount = 0;
	while (data[charCount] != '\n' && data[charCount] != '\0')
		charCount++;
	if (data[charCount] == '\0' || data[1] == '\0')
		return (0);
	tempData = ft_substr(data, charCount + 1, ft_strlen(data) - charCount);
	if (*tempData == '\0')
	{
		free(tempData);
		tempData = NULL;
	}
	data[charCount + 1] = '\0';
	return (tempData);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backupData;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024 || read(fd, 0, 0) < 0
		|| fd == 1 || fd == 2)
	{
		free(buffer);
		free(backupData);
		buffer = NULL;
		backupData = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = readDataFromFile(fd, buffer, backupData);
	free(buffer);
	if (!line)
	{
		free(backupData);
		return (NULL);
	}
	backupData = extract_line_from_buffer(line);
	return (line);
}
