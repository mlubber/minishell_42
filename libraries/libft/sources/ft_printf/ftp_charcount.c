/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftp_charcount.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 09:08:54 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/01/08 14:59:57 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_charcount(unsigned long long nbr)
{
	int	i;

	i = 1;
	while (nbr >= 16)
	{
		nbr = nbr / 16;
		i++;
	}
	return (i);
}
