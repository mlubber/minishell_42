/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 06:25:18 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/21 10:26:14 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_find_line(int fd, char *str)
{
	char	*buff;
	int		bytesread;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	bytesread = 1;
	while (!(ft_strchr_gnl(str, '\n')) && bytesread > 0)
	{
		bytesread = read(fd, buff, BUFFER_SIZE);
		if (bytesread > 0)
		{
			buff[bytesread] = '\0';
			str = ft_strjoin_gnl(str, buff);
			if (!str)
				return (ft_free(&buff));
		}
	}
	ft_free(&buff);
	if (bytesread < 0)
		return (ft_free(&str));
	return (str);
}

char	*ft_next_line(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	new = (char *)malloc((i + 1) * sizeof(char));
	if (!new)
		return (NULL);
	j = 0;
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_rem_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (ft_free(&line));
	str = (char *)malloc((ft_len(line) - i + 1) * sizeof(char));
	if (!str)
		return (ft_free(&line));
	i++;
	j = 0;
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	ft_free(&line);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*out;
	static char	*str = 0;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str = ft_find_line(fd, str);
	if (!str)
		return (NULL);
	out = ft_next_line(str);
	if (!out)
		return (ft_free(&str));
	str = ft_rem_line(str);
	return (out);
}
