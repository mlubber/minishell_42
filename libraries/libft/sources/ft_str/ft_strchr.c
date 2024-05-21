/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 08:02:41 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/17 10:46:33 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	ch;
	char	*s;

	i = 0;
	ch = c;
	s = (char *) str;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			return (s + i);
		i++;
	}
	if (ch == '\0')
		return (s + i);
	return (0);
}
