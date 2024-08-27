/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_cd_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/20 15:08:24 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/27 16:36:23 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_update_env_var(t_shell *shell, t_env *node, char *key, char *val)
{
	int		i;

	free(node->str);
	node->str = ft_strjoin(key, val);
	if (node->str == NULL)
		kill_program(shell, "Failed malloc node-str in update_env_var", errno);
	i = 0;
	while (node->str[i] != '=')
		i++;
	free(node->var_val);
	node->var_val = set_var_value(node->str + i + 1);
}

void	ft_change_path_in_env(t_shell *shell)
{
	t_env	*temp_list;

	temp_list = shell->env_list;
	while (temp_list != NULL)
	{
		if (ft_strncmp(temp_list->str, "PWD=", 4) == 0)
			ft_update_env_var(shell, temp_list, "PWD=", shell->pwd);
		else if (ft_strncmp(temp_list->str, "OLDPWD=", 7) == 0)
			ft_update_env_var(shell, temp_list, "OLDPWD=", shell->old_pwd);
		temp_list = temp_list->next;
	}
}

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
			return (tmp->str + i + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
