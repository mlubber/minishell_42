/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftp_puthexbase.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 09:06:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/01/08 15:02:33 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ftp_puthexbase(unsigned long long nbr, char *base)
{
	if (nbr >= 16)
	{
		ftp_puthexbase((nbr / 16), base);
	}
	ftp_putchar(base[nbr % 16]);
}
