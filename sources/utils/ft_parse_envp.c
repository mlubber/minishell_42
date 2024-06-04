/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parse_envp.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 08:05:43 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 06:51:28 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	getting_pwd(t_tools *tools)
{
	t_env	*tmp;

	tmp = tools->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->str, "PWD=", 4) == 0)
			tools->pwd = ft_substr(tmp->str,
					4, ft_strlen(tmp->str) - 4); // Add fail check
		if (ft_strncmp(tmp->str, "OLDPWD=", 7) == 0)
			tools->old_pwd = ft_substr(tmp->str,
					7, ft_strlen(tmp->str) - 7); // Add fail check
		tmp = tmp->next;
	}
	return (1);
}

// char	*find_path(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5)); // Add fail check
// 		i++;
// 	}
// 	return (ft_strdup("\0")); // Add fail check
// }

// int	ft_parse_envp(t_tools *tools)
// {
// 	char	*envp_path;
// 	char	*temp;
// 	int		i;

// 	envp_path = find_path(tools->envp);
// 	tools->paths = ft_split(envp_path, ':'); // Add fail check
// 	free(envp_path);
// 	i = 0;
// 	while (tools->paths[i])
// 	{
// 		if (ft_strncmp(&tools->paths[i][ft_strlen(tools->paths[i]) - 1],
// 			"/", 1) != 0)
// 		{
// 			temp = ft_strjoin(tools->paths[i], "/"); // Add fail check
// 			free(tools->paths[i]);
// 			tools->paths[i] = temp;
// 		}
// 		i++;
// 	}
// 	return (EXIT_SUCCESS);
// }

static void	getting_paths(t_tools *tools, char **envp)
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
		kill_program(tools, "envp", 1);
	tools->paths = ft_split(paths, ':');
	if (tools->paths == NULL)
		kill_program(tools, "paths", 5);
}

void	building_env(t_tools *tools, t_env **env_list, char **envp)
{
	t_env	*tmp;
	t_env	*new;
	int		i;

	*env_list = create_node(tools, envp[0]);
	tmp = *env_list;
	i = 1;
	while (envp[i] != NULL)
	{
		new = create_node(tools, envp[i]);
		tmp->next = new;
		if (tmp == NULL)
			kill_program(tools, "Failed building env!", 4);
		tmp = tmp->next;
		i++;
	}
	getting_paths(tools, envp);
	getting_pwd(tools);
}
