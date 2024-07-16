/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 10:57:13 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/16 14:23:26 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_create_env(t_shell *shell)
{
	char	**envp_array;
	int		i;
	t_env	*temp;

	envp_array = malloc((shell->env_size + 1) * sizeof(char *));
	i = 0;
	temp = shell->env_list;
	while (i < shell->env_size)
	{
		envp_array[i] = temp->str;
		// printf("env_array: %s\n", envp_array[i]);
		// if (ft_strncmp(temp->var_name, "SHLVL", 5) == 0 )
		// {
		// 	printf("string: %s\n", temp->str);
		// 	printf("shell level: %s\n", temp->var_val);
		// }
		temp = temp->next;
		i++;
	}
	envp_array[i] = NULL;
	return (envp_array);
}

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
