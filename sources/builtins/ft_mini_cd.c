/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/04 09:00:37 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 09:17:08 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_env_value(t_env *env_list, char *str)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->str, str, ft_strlen(str)) == 0)
			return (tmp->var_val);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_mini_cd(t_tools *tools)
{
	char	*path;
	int		ret;

	path = ft_get_env_value(tools->env_list, "HOME");
	if (path == NULL)
	{
		ft_putendl_fd("Error: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	printf("path: %s\n", path);
	ret = chdir(path);
	if (ret == -1)
	{
		ft_putendl_fd("Error: chdir failed", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
