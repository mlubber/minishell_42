/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_builtins_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/08 15:55:48 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/08 15:57:56 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

int	check_alpha_num(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] == '_'))
	{
		i++;
		while (str[i] != '=' && str[i] != '\0')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}
