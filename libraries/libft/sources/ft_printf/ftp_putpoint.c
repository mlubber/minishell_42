/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftp_putpoint.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 09:41:42 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/01/08 15:02:18 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_putpoint(unsigned long long l)
{
	int		len;

	len = 0;
	ftp_puthexbase(l, "0123456789abcdef");
	len = len + ftp_charcount(l);
	return (len);
}
