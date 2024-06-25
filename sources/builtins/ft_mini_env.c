/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/25 17:08:14 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Prints the environment
// *** split_input gets replaced by the command table linked list ***
int	ft_mini_env(t_shell *shell, char **split_input)
{
	t_env	*tmp;
	int		i;
	char	*path;

	tmp = shell->env_list;
	if (split_input[1] != NULL)
		printf("env: Too many arguments\n");
	else
	{
		while (tmp != NULL)
		{
			if (ft_strncmp(tmp->str, "_=", 2) == 0)
			{
				i = 0;
				while (shell->paths[i])
				{
					path = ft_strjoin(shell->paths[i], "/env");
					if (access(path, F_OK) != -1)
					{
						tmp->var_val = set_var_value(path);
						tmp->str = ft_strjoin("_=", path);
						break ;
					}
					i++;
				}
			}
			if (ft_strchr(tmp->str, '=') != NULL)
				printf("%s\n", tmp->str);
			tmp = tmp->next;
		}
	}
	return (1);
}
