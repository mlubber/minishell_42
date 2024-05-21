/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/07 17:13:30 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/22 14:42:15 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	if (((char *) dest) > ((char *) src))
	{
		while (n > 0)
		{
			n--;
			((char *) dest)[n] = ((char *) src)[n];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char *) dest)[i] = ((char *) src)[i];
			i++;
		}
	}
	return (dest);
}
