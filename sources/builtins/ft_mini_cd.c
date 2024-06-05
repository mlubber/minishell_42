/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/04 09:00:37 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 16:26:20 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	add_node_middle(t_shell *shell, t_env **head, int position, char *str)
{
	t_env	*new;
	t_env	*tmp;

	new = create_env_node(shell, str);
	if (position == 1)
	{
		new->next = *head;
		*head = new;
	}
	else
	{
		tmp = *head;
		while (position > 1)
		{
			tmp = tmp->next;
			position--;
		}
		new->next = tmp->next->next;
		tmp->next = new;
	}
}

void	ft_change_path_in_env(t_shell *shell)
{
	t_env	*temp_list;
	t_env	*temp_node;
	int		x;

	temp_list = shell->env_list;
	while (temp_list->next != NULL)
	{
		if (ft_strncmp(temp_list->next->str, "PWD=", 4) == 0)
		{
			x = temp_list->next->node_num;
			temp_node = temp_list->next;
			add_node_middle(shell, &shell->env_list, x, ft_strjoin("PWD=", shell->pwd));
			free_env_node(&temp_node);
		}
		else if (ft_strncmp(temp_list->next->str, "OLDPWD=", 7) == 0)
		{
			x = temp_list->next->node_num;
			temp_node = temp_list->next;
			add_node_middle(shell, &shell->env_list, x, ft_strjoin("OLDPWD=", shell->old_pwd));
			free_env_node(&temp_node);
		}
		temp_list = temp_list->next;
	}
}

char	*ft_get_env_value(t_env *env_list, char *str)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->str, str, ft_strlen(str)) == 0)
		{
			while (*tmp->str != '=')
				tmp->str++;
			return (tmp->str + 1);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_mini_cd(t_shell *shell)
{
	char	*path;
	int		ret;

	path = ft_get_env_value(shell->env_list, "HOME=");
	ret = chdir(path);
	if (ret == -1)
	{
		ft_putendl_fd("Error: No such file or directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	free (shell->old_pwd);
	shell->old_pwd = shell->pwd;
	shell->pwd = getcwd(NULL, 0);
	if (shell->pwd == NULL)
		kill_program(shell, "Error: getcwd failed", 6);
	ft_change_path_in_env(shell);
	return (EXIT_SUCCESS);
}
