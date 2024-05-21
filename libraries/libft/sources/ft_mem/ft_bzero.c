/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 14:53:00 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/09 14:27:56 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *) str;
	while (i < n)
	{
		s[i] = '\0';
		i++;
	}
}
