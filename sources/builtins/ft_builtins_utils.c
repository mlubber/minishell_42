/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_builtins_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/08 15:55:48 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/16 11:44:43 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_arr(char ***arr)
{
	int	i;

	i = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
}

int	check_alpha_num(char *str)
{
	int	i;

	i = 0;
	if ((str[i] >= 'a' && str[i] <= 'z')
		|| (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] == '_'))
	{
		i++;
		while (str[i] != '=' && str[i] != '\0')
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
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
	if (new_pwd == NULL)
		kill_program(shell, "Failed malloc new_pwd in path_check", errno);
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

void	ft_check_upper_dir(t_shell *shell)
{

	shell->pwd = path_check(shell, shell->old_pwd);
	while (access(shell->pwd, F_OK) == -1)
		shell->pwd = path_check(shell, shell->pwd);
	chdir(shell->pwd);
}

void	replace_var_value(t_shell *shell, t_env *temp, char *input, int len)
{
	if (temp->var_val != NULL)
		free(temp->var_val);
	temp->var_val = set_var_value(input + len + 1);
	if (temp->str != NULL)
		free(temp->str);
	temp->str = ft_strdup(input);
	if (temp->var_val == NULL)
		kill_program(shell, "Failed mallocing env var value!", errno);
}
