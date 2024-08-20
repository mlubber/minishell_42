/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/04 09:00:37 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/20 15:14:46 by mlubbers      ########   odam.nl         */
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

int	squigly_wiggly(t_shell *shell, char **input, char *home_value)
{
	int	ret;

	if (home_value != NULL)
		home_value = ft_strjoin(home_value, input[1] + 1);
	else
		home_value = ft_strjoin(shell->home, input[1] + 1);
	ret = chdir(home_value);
	free(home_value);
	return (ret);
}

int	ft_change_directory(t_shell *shell, char **input)
{
	char	*home_value;

	home_value = ft_get_env_value(shell->env_list, "HOME=");
	if (input[1] != NULL && input[1][0] == '~'
		&& input[1][1] == '\0' && home_value == NULL)
		return (chdir(shell->home));
	else if (input[1] != NULL && input[1][0] == '~'
		&& input[1][1] == '\0' && home_value != NULL)
		return (chdir(home_value));
	if (input[1] == NULL || (input[1][0] == '-'
		&& input[1][1] == '-' && input[1][2] == '\0'))
		if (home_value == NULL)
			return (-2);
	if (input[1] == NULL && home_value != NULL)
		return (chdir(home_value));
	else if (input[1] != NULL && input[1][0] == '-' && input[1][1] == '-'
		&& input[1][2] == '\0')
		return (chdir(home_value));
	else if (input[1] != NULL && input[1][0] == '-' && input[1][1] == '\0')
		return (chdir(ft_get_env_value(shell->env_list, "OLDPWD=")));
	else if (input[1] != NULL && input[1][0] == '~' && input[1][1] != '\0')
		return (squigly_wiggly(shell, input, home_value));
	else
		return (chdir(input[1]));
}

// Works like the 'cd' function. Using 'cd' or 'cd sources' work, for example
void	ft_mini_cd(t_shell *shell, char **split_input)
{
	int	ret;

	if (split_input[1] != NULL && split_input[2] != NULL)
	{
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
		shell->exit_code = 1;
		return ;
	}
	ret = ft_change_directory(shell, split_input);
	if (ret == -1 || ret == -2)
	{
		if (ret == -1)
			ft_putendl_fd("Error: No such file or directory", STDERR_FILENO);
		if (ret == -2)
			ft_putendl_fd("Error: HOME not set", STDERR_FILENO);
		shell->exit_code = 1;
		return ;
	}
	free (shell->old_pwd);
	shell->old_pwd = shell->pwd;
	shell->pwd = getcwd(NULL, 0);
	if (shell->pwd == NULL)
		ft_check_upper_dir(shell);
	ft_change_path_in_env(shell);
	shell->exit_code = 0;
}

