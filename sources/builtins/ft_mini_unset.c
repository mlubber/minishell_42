/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 12:10:52 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/17 13:33:58 by mlubbers      ########   odam.nl         */
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

// Will delete the node and set the next pointers in the prior and latter node correctly.
// Currently does not work and needs to be split up in multiple functions probably
// void	delete_var(t_env **head, int position)
// {
// 	t_env	*tmp;
// 	t_env	*old;

// 	tmp = *head;
// 	old = NULL;
// 	if (*head == NULL)
// 		printf("DEL MID: Linked List already empty!\n");
// 	else if (position == 1)
// 	{
// 		*head = (*head)->next;
// 		free(tmp);
// 	}
// 	else if (position > count_nodes(*head))
// 	{
// 		printf("Node #%d is bigger than list size\n", position);
// 		exit(1);
// 	}
// 	else if (position == count_nodes(*head))
// 	{
// 		while (tmp->next->next != NULL)
// 			tmp = tmp->next;
// 		free(tmp->next);
// 		tmp->next = NULL;
// 	}
// 	else
// 	{
// 		while (position > 2)
// 		{
// 			tmp = tmp->next;
// 			position--;
// 		}
// 		old = tmp->next;
// 		tmp->next = tmp->next->next;
// 		free(old);
// 	}
// }

// Will delete the node and set the next pointers in the prior and latter node correctly.
// Currently does not work
// *** split_input gets replaced by the command table linked list ***
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
			shell->env_size--;
			break ;
		}
		i++;
	}
	return (1);
}
