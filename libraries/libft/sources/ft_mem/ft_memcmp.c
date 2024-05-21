/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/15 13:31:43 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/17 10:46:57 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *mem1, const void *mem2, size_t n)
{
	size_t			i;
	int				d;
	unsigned char	*m1;
	unsigned char	*m2;

	m1 = (unsigned char *) mem1;
	m2 = (unsigned char *) mem2;
	i = 0;
	while (i < n)
	{
		d = (m1[i] - m2[i]);
		if ((m1[i] != m2[i]))
			return (d);
		i++;
	}
	return (0);
}
