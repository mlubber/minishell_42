/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parse_envp.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 08:05:43 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 16:29:04 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	getting_pwd(t_shell *shell)
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

static void	getting_paths(t_shell *shell, char **envp)
{
	int		i;
	char	*paths;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (envp[i] == NULL)
		kill_program(shell, "Couldn't find env", 1);
	shell->paths = ft_split(paths, ':');
	if (shell->paths == NULL)
		kill_program(shell, "Failed mallocing paths", 6);
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
		shell->env_size++;
		i++;
	}
	getting_paths(shell, envp);
	getting_pwd(shell);
}
