/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 13:28:31 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/21 15:35:45 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cmd_not_found(char **cmd)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	ft_putstr_fd(": command not found\n", 2);
	ft_free_arr(&cmd);
	exit(127);
}

void	ft_not_found_free(char **cmds, char **paths, char **envp)
{
	DIR	*dir;

	ft_free_arr(&paths);
	ft_free_arr(&envp);
	dir = opendir(cmds[0]);
	if (dir && ft_strnstr(cmds[0], "/", ft_strlen(cmds[0])))
	{
		write(2, cmds[0], ft_strlen(cmds[0]));
		ft_putstr_fd(": Is a directory\n", 2);
		ft_free_arr(&cmds);
		closedir(dir);
		exit(126);
	}
	else if (dir == NULL && ft_strnstr(cmds[0], "/", ft_strlen(cmds[0])))
	{
		write(2, cmds[0], ft_strlen(cmds[0]));
		ft_putstr_fd(": No such file or directory\n", 2);
		ft_free_arr(&cmds);
		closedir(dir);
		exit(127);
	}
	else
		ft_cmd_not_found(cmds);
}

char	*ft_connectstring(char const *s1, char const *s2, char c)
{
	int		i;
	int		o;
	char	*p;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	o = ft_strlen(s1) + ft_strlen(s2);
	p = malloc((o + 2) * sizeof(char));
	if (!p)
		return (NULL);
	while (*s1)
		p[i++] = *s1++;
	p[i] = c;
	i++;
	while (*s2)
		p[i++] = *s2++;
	p[i] = '\0';
	return (p);
}

char	**ft_get_paths(t_shell *shell)
{
	char	*paths;
	char	**split_paths;
	t_env	*tmp;

	tmp = shell->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, "PATH", 5) == 0)
		{
			paths = tmp->var_val;
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (NULL);
	split_paths = ft_split(paths, ':');
	if (split_paths == NULL)
		kill_program(shell, "failed mallocing split_paths", errno);
	return (split_paths);
}
