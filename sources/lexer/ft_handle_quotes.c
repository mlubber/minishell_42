/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_quotes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 15:50:52 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/03 10:01:11 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_handle_quotes(int i, char *str, char c)
{
	int	j;

	j = 0;
	if (str[i + j] == c)
	{
		j++;
		while (str[i + j] != c && str[i + j])
			j++;
		if (str[i + j] == '\0')
		{
			j = 0;
			if (str[i + j] == c)
				j++;
			while (str[i + j] && ft_is_whitespace(str[i + j]) == 0)
				j++;
			return (j);
		}
		else
			j++;
	}
	return (j);
}

