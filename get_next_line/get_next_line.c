/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:22:09 by ckannane          #+#    #+#             */
/*   Updated: 2023/10/07 12:32:09 by ckannane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define BUFFER_SIZE 6

char	*ft_save(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 2), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free (buffer);
	return (line);
}

char	*put_line(char *save)
{
	int		i;
	char	*s;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	s = ft_substr(save, 0, i + 1);
	return (s);
}

char	*read_line(int fd, char *res)
{
	char	*buffer;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (NULL);
		buffer[byte_read] = '\0';
		res = ft_strjoin(res, buffer);
		if (ft_strchro(buffer, '\n'))
			break ;
	}
	free(buffer);
	if (!res)
		return (NULL);
	return (res);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd == 1 || fd == 2)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = put_line(buffer);
	buffer = ft_save(buffer);
	return (line);
}
