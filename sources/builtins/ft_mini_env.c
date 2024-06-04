/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 16:30:22 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_mini_env(t_tools *tools)
{
	t_env	*tmp;

	tmp = tools->env_list;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}

