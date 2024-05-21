/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftp_putstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:47:48 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/01/08 15:02:10 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ftp_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i] != '\0')
	{
		ftp_putchar(s[i]);
		i++;
	}
	return (i);
}
