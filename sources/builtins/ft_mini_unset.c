/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 12:10:52 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/07/08 16:00:08 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	search_and_delete_var(t_env **head, char *str)
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

// Will delete the node and set the next pointers in the prior and latter node correctly. Updates the node_num accordingly
int	ft_mini_unset(t_shell *shell, char **split_input)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = shell->env_list;
	if (split_input[1] == NULL)
		return (1);
	while (split_input[i] != NULL)
	{
		if (search_and_delete_var(&tmp, split_input[i]) != 0)
		{
			while (tmp->next != NULL)
			{
				if (tmp->next->node_num - tmp->node_num > 1)
					tmp->next->node_num = tmp->node_num + 1;
				tmp = tmp->next;
			}
			shell->env_size--;
			break ;
		}
		i++;
	}
	return (1);
}
