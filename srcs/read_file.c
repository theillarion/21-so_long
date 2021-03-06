/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glashli <glashli@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:52:48 by glashli           #+#    #+#             */
/*   Updated: 2022/04/20 14:54:28 by glashli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*ft_read_full_file(int fd)
{
	char	*file;
	char	*buff;
	char	*backup;
	int		count;

	buff = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	file = NULL;
	count = read(fd, buff, BUFFER_SIZE);
	if (count > 0)
	{
		file = (char *)ft_calloc(1, sizeof(char));
		buff[count] = '\0';
	}
	while (count > 0)
	{
		backup = file;
		file = ft_strjoin(file, buff);
		ft_smart_free((void **)&backup);
		count = read(fd, buff, BUFFER_SIZE);
		if (count >= 0)
			buff[count] = '\0';
	}
	ft_smart_free((void **)&buff);
	return (file);
}

static bool	ft_check_path(const char	*path)
{
	size_t	i;

	i = strlen(path) - 1;
	if (path[i - 3] == '.' && path[i - 2] == 'b'
		&& path[i - 1] == 'e' && path[i] == 'r')
		return (true);
	return (false);
}

static bool	ft_return_and_close(int fd)
{
	close(fd);
	return (false);
}

bool	ft_get_file(t_file	*file, const char	*path)
{
	int		fd;
	char	*buff;

	if (file == NULL || path == NULL || *path == '\0')
		return (false);
	if (ft_check_path(path) == false)
		return (false);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (false);
	buff = ft_read_full_file(fd);
	if (buff == NULL || *buff == '\0' || buff[ft_strlen(buff) - 1] == '\n')
		return (ft_return_and_close(fd));
	file->lines = ft_split(buff, '\n');
	ft_smart_free((void **)&buff);
	file->length = ft_strlen(file->lines[0]);
	file->count = 0;
	while (file->lines[file->count] != NULL)
		file->count++;
	close(fd);
	if (fd < 0)
		return (false);
	return (true);
}
