/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/26 19:22:45 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_create_env(t_shell *shell)
{
	char	**envp_array;
	int		i;
	t_env	*temp;

	envp_array = malloc((shell->env_size + 1) * sizeof(char *));
	if (envp_array == NULL)
		kill_program(shell, "Failed mallocing envp array in mini_env", errno);
	i = 0;
	temp = shell->env_list;
	while (i < shell->env_size)
	{
		envp_array[i] = temp->str;
		temp = temp->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

void	ft_mini_env(t_shell *shell, char **split_input)
{
	t_env	*tmp;

	tmp = shell->env_list;
	if (split_input[1] != NULL)
	{
		ft_putendl_fd("env: Too many arguments", STDERR_FILENO);
		shell->exit_code = 1;
	}
	else
	{
		while (tmp != NULL)
		{
			if (ft_strchr(tmp->str, '=') != NULL)
				ft_putendl_fd(tmp->str, STDOUT_FILENO);
			tmp = tmp->next;
		}
		shell->exit_code = 0;
	}
}
