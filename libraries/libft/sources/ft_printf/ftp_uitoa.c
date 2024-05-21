/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftp_uitoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 15:36:48 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/01/08 15:02:02 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long	countdigits(long n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

int	ftp_uitoa(int n)
{
	unsigned int	u;
	int				size;

	size = 0;
	u = (unsigned int)n;
	size = size + countdigits(u);
	ftp_putnbr(u);
	return (size);
}
