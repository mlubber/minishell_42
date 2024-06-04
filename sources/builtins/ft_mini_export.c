/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 11:01:03 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 12:53:48 by mlubbers      ########   odam.nl         */
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

int	ft_mini_export(t_tools *tools)
{
	int		i;
	int		count;
	char	**export_list;
	t_env	*tmp;

	count = tools->env_size;
	export_list = malloc((count + 1) * sizeof(char *));
	if (export_list == NULL)
		return (EXIT_FAILURE);
	i = 0;
	tmp = tools->env_list;
	while (i < count)
	{
		export_list[i] = ft_strjoin(ft_strjoin(tmp->var_name, "="),
				tmp->var_val);
		i++;
		tmp = tmp->next;
	}
	export_list[i] = NULL;
	ft_sort_env_lines(export_list, count);
	i = 0;
	while (i < count - 1)
		printf("declare -x %s\n", export_list[i++]);
	ft_free_2d_arr(export_list);
	return (EXIT_SUCCESS);
}
