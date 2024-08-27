/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/04 09:00:37 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/27 17:06:39 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cd_error(t_shell *shell, int error)
{
	if (error == -1)
		ft_putendl_fd("Error: No such file or directory", STDERR_FILENO);
	if (error == -2)
		ft_putendl_fd("Error: HOME not set", STDERR_FILENO);
	if (error == -3)
		ft_putendl_fd("Error: OLDPWD not set", STDERR_FILENO);
	if (error == -4)
		ft_putendl_fd("Error: CD does not take flags", STDERR_FILENO);
	shell->exit_code = 1;
}

static int	dash(t_shell *shell, char **input, char *home_value)
{
	if (input[1][0] == '-' && input[1][1] == '-' && input[1][2] == '\0')
	{
		if (home_value == NULL)
			return (-2);
		else
			return (chdir(home_value));
	}
	else if (input[1] != NULL && input[1][0] == '-' && input[1][1] == '\0')
	{
		if (shell->old_pwd == NULL)
			return (-3);
		else
		{
			ft_putendl_fd(shell->old_pwd, STDOUT_FILENO);
			return (chdir(shell->old_pwd));
		}
	}
	else
		return (-4);
}

static int	tilde(t_shell *shell, char **input, char *home_value)
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

static int	ft_change_directory(t_shell *shell, char **input)
{
	char	*home_value;

	home_value = ft_get_env_value(shell->env_list, "HOME=");
	if (input[1] == NULL && home_value != NULL)
		return (chdir(home_value));
	else if (input[1] == NULL && home_value == NULL)
		return (-2);
	if (input[1] != NULL && input[1][0] == '~'
		&& input[1][1] == '\0' && home_value == NULL)
		return (chdir(shell->home));
	else if (input[1] != NULL && input[1][0] == '~'
		&& input[1][1] == '\0' && home_value != NULL)
		return (chdir(home_value));
	if (input[1] != NULL && input[1][0] == '-')
		return (dash(shell, input, home_value));
	else if (input[1] != NULL && input[1][0] == '~' && input[1][1] != '\0')
		return (tilde(shell, input, home_value));
	else
		return (chdir(input[1]));
}

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
	if (ret < 0)
	{
		cd_error(shell, ret);
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
