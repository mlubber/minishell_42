/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_builtin_utils_2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 15:08:24 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/20 15:08:35 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_get_env_value(t_env *env_list, char *str)
{
	t_env	*tmp;
	int		i;

	tmp = env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->str, str, ft_strlen(str)) == 0)
		{
			i = 0;
			while (tmp->str[i] != '=')
				i++;
			if (ft_strncmp("OLDPWD=", str, ft_strlen(str)) == 0)
				ft_putendl_fd(tmp->str + i + 1, STDERR_FILENO);
			return (tmp->str + i + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
