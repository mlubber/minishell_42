/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 06:25:46 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/21 10:23:12 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

size_t	ft_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	size_t	i;
	size_t	j;
	char	*out;

	if (!str1)
		i = ft_len(str2);
	else
		i = ft_len(str1) + ft_len(str2);
	out = (char *)malloc((i + 1) * sizeof(char));
	if (!out)
		return (ft_free(&str1));
	i = 0;
	while (str1 != NULL && str1[i])
	{
		out[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
		out[i++] = str2[j++];
	out[i] = '\0';
	ft_free(&str1);
	return (out);
}
