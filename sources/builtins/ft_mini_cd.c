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


void	add_node_middle(t_tools *tools, t_env **head, int position, char *str)
{
	t_env	*new;
	t_env	*tmp;
	int		i;

	i = 0;
	new = create_node(tools, str);
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

void	ft_change_path_in_env(t_tools *tools)
{
	t_env	*temp_list;
	t_env	*temp_node;
	int		x;

	temp_list = tools->env_list;
	while (temp_list->next != NULL)
	{
		if (ft_strncmp(temp_list->next->str, "PWD=", 4) == 0)
		{
			x = temp_list->next->node_num;
			temp_node = temp_list->next;
			add_node_middle(tools, &tools->env_list, x, ft_strjoin("PWD=", tools->pwd));
			free_env_node(&temp_node);
		}
		else if (ft_strncmp(temp_list->next->str, "OLDPWD=", 7) == 0)
		{
			x = temp_list->next->node_num;
			temp_node = temp_list->next;
			add_node_middle(tools, &tools->env_list, x, ft_strjoin("OLDPWD=", tools->old_pwd));
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

int	ft_mini_cd(t_tools *tools)
{
	char	*path;
	int		ret;

	path = ft_get_env_value(tools->env_list, "HOME=");
	ret = chdir(path);
	if (ret == -1)
	{
		ft_putendl_fd("Error: No such file or directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	free (tools->old_pwd);
	tools->old_pwd = tools->pwd;
	tools->pwd = getcwd(NULL, 0);
	if (tools->pwd == NULL)
		kill_program(tools, "Error: getcwd failed", 6);
	ft_change_path_in_env(tools);
	return (EXIT_SUCCESS);
}
