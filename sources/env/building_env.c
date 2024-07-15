/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   building_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 08:05:43 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/15 17:09:40 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setting_pwd(t_shell *shell)
{
	t_env	*tmp;

	tmp = shell->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->str, "PWD=", 4) == 0)
		{
			shell->pwd = ft_substr(tmp->str, 4, ft_strlen(tmp->str) - 4);
			if (shell->pwd == NULL)
				kill_program(shell, "Failed mallocing PWD!", 6);
		}
		if (ft_strncmp(tmp->str, "OLDPWD=", 7) == 0)
		{
			shell->old_pwd = ft_substr(tmp->str, 7, ft_strlen(tmp->str) - 7);
			if (shell->old_pwd == NULL)
				kill_program(shell, "Failed mallocing OLD_PWD!", 6);
		}
		tmp = tmp->next;
	}
}

void	building_env(t_shell *shell, t_env **env_list, char **envp)
{
	t_env	*tmp;
	t_env	*new;
	int		i;

	*env_list = create_env_node(shell, envp[0]);
	tmp = *env_list;
	i = 1;
	while (envp[i] != NULL)
	{
		new = create_env_node(shell, envp[i]);
		tmp->next = new;
		if (tmp == NULL)
			kill_program(shell, "Failed building env!", 6);
		tmp = tmp->next;
		i++;
	}
	setting_pwd(shell);
}
