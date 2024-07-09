/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/09 10:35:22 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Prints the environment
int	ft_mini_env(t_shell *shell, char **split_input)
{
	t_env	*tmp;

	tmp = shell->env_list;
	if (split_input[1] != NULL)
		printf("env: Too many arguments\n");
	else
	{
		while (tmp != NULL)
		{
			if (ft_strchr(tmp->str, '=') != NULL)
				ft_putendl_fd(tmp->str, STDOUT_FILENO);
			tmp = tmp->next;
		}
	}
	return (1);
}
