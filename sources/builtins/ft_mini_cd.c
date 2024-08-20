/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/04 09:00:37 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/19 16:21:25 by mlubbers      ########   odam.nl         */
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

static void	ft_change_path_in_env(t_shell *shell)
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
			if (ft_strncmp("OLDPWD=", str, ft_strlen(str)) == 0)
				ft_putendl_fd(tmp->str + i + 1, STDERR_FILENO);
			return (tmp->str + i + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_change_directory(t_shell *shell, char **split_input)
{
	int		ret;
	char	*home_value;
	char	*home_joined;

	home_value = ft_get_env_value(shell->env_list, "HOME=");
	if (split_input[1] != NULL && split_input[1][0] == '~')
		if (home_value == NULL)
			return (-2);
	if (split_input[1] == NULL
		|| (split_input[1][0] == '~' && split_input[1][1] == '\0'))
		ret = chdir(home_value);
	else if (split_input[1][0] == '-' && split_input[1][1] == '-'
		&& split_input[1][2] == '\0')
		ret = chdir(home_value);
	else if (split_input[1][0] == '-' && split_input[1][1] == '\0')
		ret = chdir(ft_get_env_value(shell->env_list, "OLDPWD="));
	else if (split_input[1][0] == '~' && split_input[1][1] != '\0')
	{
		home_joined = ft_strjoin(home_value, split_input[1] + 1);
		ret = chdir(home_joined);
		free(home_joined);
	}
	else
		ret = chdir(split_input[1]);
	return (ret);
}

// Works like the 'cd' function. Using 'cd' or 'cd sources' work, for example
int	ft_mini_cd(t_shell *shell, char **split_input)
{
	int	ret;

	if (split_input[1] != NULL && split_input[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		shell->exit_code = 1;
		if (shell->pid == 0)
			kill_program(shell, NULL, 1);
		return (1);
	}
	ret = ft_change_directory(shell, split_input);
	if (ret == -1 || ret == -2)
	{
		if (ret == -1)
			ft_putendl_fd("Error: No such file or directory", STDERR_FILENO);
		if (ret == -2)
			ft_putendl_fd("Error: HOME not set", STDERR_FILENO);
		return (1);
	}
	free (shell->old_pwd);
	shell->old_pwd = shell->pwd;
	shell->pwd = getcwd(NULL, 0);
	if (shell->pwd == NULL)
		ft_check_upper_dir(shell);
	ft_change_path_in_env(shell);
	return (0);
}

