/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parse_envp.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 08:05:43 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/27 12:02:20 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_find_pwd(t_tools *tools)
{
	int	i;

	i = 0;
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], "PWD=", 4) == 0)
		{
			tools->pwd = ft_substr(tools->envp[i],
					4, ft_strlen(tools->envp[i]) - 4);
		}
		if (ft_strncmp(tools->envp[i], "OLDPWD=", 7) == 0)
		{
			tools->old_pwd = ft_substr(tools->envp[i],
					7, ft_strlen(tools->envp[i]) - 7);
		}
		i++;
	}
	return (1);
}

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}

int	ft_parse_envp(t_tools *tools)
{
	char	*envp_path;
	char	*temp;
	int		i;

	envp_path = find_path(tools->envp);
	tools->paths = ft_split(envp_path, ':');
	free(envp_path);
	i = 0;
	while (tools->paths[i])
	{
		if (ft_strncmp(&tools->paths[i][ft_strlen(tools->paths[i]) - 1],
			"/", 1) != 0)
		{
			temp = ft_strjoin(tools->paths[i], "/");
			free(tools->paths[i]);
			tools->paths[i] = temp;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
