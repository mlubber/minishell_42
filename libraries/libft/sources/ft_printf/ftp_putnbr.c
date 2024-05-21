/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftp_putnbr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/28 09:11:44 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/01/08 15:02:25 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ftp_putnbr(long n)
{
	if (n > 9)
	{
		ftp_putnbr(n / 10);
	}
	ftp_putchar((n % 10 + '0'));
}
