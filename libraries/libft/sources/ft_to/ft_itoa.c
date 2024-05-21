/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 14:34:00 by mlubbers      #+#    #+#                 */
/*   Updated: 2023/10/23 13:43:10 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countdigits(int n)
{
	int		i;
	long	num;

	num = n;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		num = num * -1;
		i = 1;
	}
	else
		i = 0;
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		index;
	long	num;

	num = (long)n;
	index = countdigits(n) - 1;
	str = (char *)malloc((countdigits(n) + 1) * sizeof(char));
	if (str == 0)
		return (NULL);
	if (n == -2147483648)
		num = 2147483648;
	else if (num < 0)
		num = num * -1;
	str[countdigits(n)] = '\0';
	while (index >= 0)
	{
		str[index] = (num % 10) + '0';
		num = num / 10;
		index--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
