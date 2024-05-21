/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftp_puthex.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 07:56:30 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/01/08 15:00:34 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_puthex(int i, char x)
{
	char			*base;
	int				len;
	unsigned int	c;

	base = "0123456789abcdef";
	if (x == 'X')
		base = "0123456789ABCDEF";
	len = 0;
	c = (unsigned int)i;
	ftp_puthexbase(c, base);
	len = len + ftp_charcount(c);
	return (len);
}
