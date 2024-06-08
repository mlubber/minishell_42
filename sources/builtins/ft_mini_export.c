/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 11:01:03 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/07 13:02:19 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_sort_env_lines(char **envp, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strncmp(envp[i], envp[j], ft_strlen(envp[i])) > 0)
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
}

// Works fine
// *** split_input gets replaced by the command table linked list ***
int	ft_mini_export(t_shell *shell, char **split_input)
{
	int		i;
	char	**export_list;
	t_env	*tmp;

	if (split_input[1] != NULL)
		printf("export: Too many arguments");
	else
	{
		export_list = malloc((shell->env_size + 1) * sizeof(char *));
		if (export_list == NULL)
			return (EXIT_FAILURE);
		i = 0;
		tmp = shell->env_list;
		while (i < shell->env_size)
		{
			export_list[i] = ft_strjoin(ft_strjoin(tmp->var_name, "="),
					tmp->var_val);
			i++;
			tmp = tmp->next;
		}
		export_list[i] = NULL;
		ft_sort_env_lines(export_list, shell->env_size);
		i = 0;
		while (i < shell->env_size - 1)
			printf("declare -x %s\n", export_list[i++]);
		ft_free_2d_arr(&export_list, 0);
	}
	return (true);
}
