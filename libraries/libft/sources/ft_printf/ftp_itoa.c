/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftp_itoa.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 14:10:57 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/01/08 15:01:16 by mlubbers      ########   odam.nl         */
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

int	ftp_itoa(int n)
{
	long	l;
	int		size;

	size = 0;
	l = n;
	if (l < 0)
	{
		ftp_putchar('-');
		l = l * -1;
		size++;
	}
	size = size + countdigits(l);
	ftp_putnbr(l);
	return (size);
}
