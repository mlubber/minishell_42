/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_handle_quotes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 15:50:52 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/28 16:53:40 by mlubbers      ########   odam.nl         */
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
		j++;
	}
	return (j);
}
