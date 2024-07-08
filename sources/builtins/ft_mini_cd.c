/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/04 09:00:37 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/08 15:51:13 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_change_path_in_env(t_shell *shell)
{
	t_env	*temp_list;
	int		i;

	temp_list = shell->env_list;
	while (temp_list->next != NULL)
	{
		i = 0;
		if (ft_strncmp(temp_list->next->str, "PWD=", 4) == 0)
		{
			temp_list->next->str = ft_strjoin("PWD=", shell->pwd);
			while (temp_list->next->str[i] != '=')
				i++;
			temp_list->next->var_val
				= set_var_value(temp_list->next->str + i + 1);
		}
		else if (ft_strncmp(temp_list->next->str, "OLDPWD=", 7) == 0)
		{
			temp_list->next->str = ft_strjoin("OLDPWD=", shell->old_pwd);
			while (temp_list->next->str[i] != '=')
				i++;
			temp_list->next->var_val
				= set_var_value(temp_list->next->str + i + 1);
		}
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
				printf("%s\n", tmp->str + i + 1);
			return (tmp->str + i + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_get_full_path(t_env *env_list, char *str)
{
	char	*home;
	char	*join;

	home = ft_get_env_value(env_list, "HOME=");
	join = ft_strjoin(home, str + 1);
	return (join);
}

int	ft_change_directory(t_shell *shell, char **split_input)
{
	int		ret;
	char	*home_value;

	home_value = ft_get_env_value(shell->env_list, "HOME=");
	if (split_input[1] != NULL && split_input[1][0] == '~')
		if (home_value == NULL)
			return (-2);
	if (split_input[1] == NULL
		|| (split_input[1][0] == '~' && split_input[1][1] == '\0'))
		ret = chdir(home_value);
	else if (split_input[1][0] == '-' && split_input[1][1] == '\0')
		ret = chdir(ft_get_env_value(shell->env_list, "OLDPWD="));
	else if (split_input[1][0] == '~' && split_input[1][1] != '\0')
		ret = chdir(ft_get_full_path(shell->env_list, split_input[1]));
	else
	{
		ret = chdir(split_input[1]);
	}
	return (ret);
}

char	*path_check(t_shell *shell, char *path)
{
	int		i;
	char	*new_pwd;

	i = ft_strlen(path) - 1;
	if (path[i] == '/')
		i--;
	while (path[i] != '/')
		i--;
	new_pwd = malloc((i + 1) * sizeof(char));
	new_pwd[i] = '\0';
	i--;
	while (i >= 0)
	{
		new_pwd[i] = path[i];
		i--;
	}
	if (shell->pwd != NULL)
		free (shell->pwd);
	return (new_pwd);
}

// Works like the 'cd' function. Using 'cd' or 'cd sources' work, for example
int	ft_mini_cd(t_shell *shell, char **split_input)
{
	int	ret;

	if (split_input[1] != NULL && split_input[2] != NULL)
	{
		printf("cd: Too many arguments");
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
	{
		shell->pwd = path_check(shell, shell->old_pwd);
		while (access(shell->pwd, F_OK) == -1)
			shell->pwd = path_check(shell, shell->pwd);
		chdir(shell->pwd);
	}
	ft_change_path_in_env(shell);
	return (1);
}

