/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ftp_printf.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:20:57 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/01/08 15:01:07 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conversions(char c, va_list args)
{
	unsigned long long	p;

	if (c == 'c')
		return (ftp_putchar(va_arg(args, int)));
	else if (c == 's')
		return (ftp_putstr(va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ftp_itoa(va_arg(args, int)));
	else if (c == 'u')
		return (ftp_uitoa(va_arg(args, int)));
	else if (c == 'x' || c == 'X')
		return (ftp_puthex(va_arg(args, int), c));
	else if (c == '%')
		return (ftp_putchar('%'));
	else if (c == 'p')
	{
		p = va_arg(args, unsigned long long);
		if (p == 0)
			return (ftp_putstr("(nil)"));
		else
			return (ftp_putstr("0x") + ftp_putpoint(p));
	}
	return (0);
}

int	ftp_printf(const char *format, ...)
{
	unsigned int	i;
	unsigned int	len;
	va_list			arg;

	if (!format)
		return (0);
	va_start(arg, format);
	i = 0;
	len = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			len = len + conversions(format[i], arg);
		}
		else
			len = len + ftp_putchar(format[i]);
		i++;
	}
	va_end(arg);
	return (len);
}
