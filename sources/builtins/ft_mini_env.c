/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/03 19:38:59 by wsonepou      ########   odam.nl         */
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

// int	ft_mini_env(t_tools *tools)
// {
// 	int	i;

// 	i = 0;
// 	while (tools->envp[i])
// 	{
// 		ft_putendl_fd(tools->envp[i], STDOUT_FILENO);
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }
