/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   building_env.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 08:05:43 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/05 10:59:58 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_max_lvl(int value)
{
	value++;
	if (value > 999)
	{
		ft_putstr_fd("minishell: warning: shell level (1000) ", 0);
		ft_putendl_fd("too high, resetting to 1", 0);
		value = 1;
	}
	return (value);
}

void	setting_shlvl(t_shell *shell)
{
	t_env	*temp;
	char	**split_str;
	int		value;
	char	*input;

	temp = shell->env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->var_name, "SHLVL", 6) == 0)
		{
			split_str = ft_split(temp->str, '=');
			value = ft_atoi(split_str[1]);
			value = ft_max_lvl(value);
			free(split_str[1]);
			split_str[1] = ft_itoa(value);
			input = ft_connectstring(split_str[0], split_str[1], '=');
			add_export_node(shell, input);
			ft_free_arr(&split_str);
			free(input);
		}
		temp = temp->next;
	}
}

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
	setting_shlvl(shell);
	setting_pwd(shell);
}
