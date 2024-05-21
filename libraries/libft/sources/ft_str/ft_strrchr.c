/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/10 08:33:57 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/10 08:40:36 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*chr;

	chr = (char *) str;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return (chr + i);
		i--;
	}
	return (0);
}
