/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 13:28:31 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/08/27 14:27:31 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cmd(t_shell *shell, char *cmd, char **cmd_array, char **envp)
{
	if (close(shell->stdinput) == -1)
		perror("shell->stdinput");
	if (close(shell->stdoutput) == -1)
		perror("shell->stdoutput");
	init_signals(shell, 2);
	execve(cmd, cmd_array, envp);
}

void	cmd_not_found(t_shell *shell, char **cmd)
{
	errno = 0;
	write(2, cmd[0], ft_strlen(cmd[0]));
	ft_putstr_fd(": command not found\n", 2);
	kill_program(shell, NULL, 127);
}

void	check_if_dir(t_shell *shell, char **cmds)
{
	DIR	*dir;

	dir = opendir(cmds[0]);
	if (dir)
	{
		write(2, cmds[0], ft_strlen(cmds[0]));
		ft_putstr_fd(": Is a directory\n", 2);
		if (closedir(dir) == -1)
			ft_putstr_fd("Failed closing dir\n", 2);
		kill_program(shell, NULL, 126);
	}
	else if (dir == NULL)
	{
		write(2, cmds[0], ft_strlen(cmds[0]));
		ft_putstr_fd(": No such file or directory\n", 2);
		kill_program(shell, NULL, 127);
	}
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
