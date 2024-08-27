/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 12:10:52 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/27 16:55:07 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	search_and_delete_var(t_env **head, char *str)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	prev = NULL;
	if (temp != NULL
		&& ft_strncmp(temp->var_name, str, ft_strlen(str) + 1) == 0)
	{
		*head = temp->next;
		free(temp);
	}
	while (temp != NULL
		&& ft_strncmp(temp->var_name, str, ft_strlen(str) + 1) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (false);
	prev->next = temp->next;
	free_env_node(&temp);
	return (true);
}

static void	check_if_oldpwd(t_shell *shell, char *str)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = "OLDPWD";
	while (str[i])
	{
		if (str[i] != oldpwd[i])
			return ;
		i++;
	}
	if (str[i] != oldpwd[i])
		return ;
	free(shell->old_pwd);
	shell->old_pwd = NULL;
}

void	ft_mini_unset(t_shell *shell, char **split_input)
{
	int		i;
	t_env	*tmp;

	i = 1;
	tmp = shell->env_list;
	if (split_input[1] == NULL)
		return ;
	while (split_input[i] != NULL)
	{
		check_if_oldpwd(shell, split_input[1]);
		if (search_and_delete_var(&tmp, split_input[i]) != 0)
		{
			while (tmp->next != NULL)
			{
				if (tmp->next->node_num - tmp->node_num > 1)
					tmp->next->node_num = tmp->node_num + 1;
				tmp = tmp->next;
			}
			shell->env_size--;
			tmp = shell->env_list;
		}
		i++;
	}
}
