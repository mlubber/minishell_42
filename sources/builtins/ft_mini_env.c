/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/13 17:19:16 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Prints the environment
// *** split_input gets replaced by the command table linked list ***
int	ft_mini_env(t_shell *shell, char **cmds)
{
	t_env	*tmp;

	tmp = shell->env_list;
	if (cmds[1] != NULL)
		printf("env: Too many arguments");
	else
	{
		while (tmp != NULL)
		{
			printf("%s\n", tmp->str);
			tmp = tmp->next;
		}
	}
	return (1);
}
