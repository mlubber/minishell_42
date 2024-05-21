/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 14:34:51 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/22 14:15:30 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int ch, size_t n)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *) str;
	while (i < n)
	{
		s[i] = ch;
		i++;
	}
	return (s);
}
