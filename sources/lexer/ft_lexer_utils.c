/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lexer_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:40:42 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/07 12:32:45 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ctable	*ft_new_lexer_node(char *str)
{
	t_ctable		*new_node;
	static int	i = 0;

	new_node = (t_ctable *)malloc(sizeof(t_ctable));
	if (new_node == NULL)
		return (0);
	new_node->str = str;
	new_node->node_nbr = i++;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lexer_add_back(t_ctable **lexer_list, t_ctable *new)
{
	t_ctable	*temp;

	temp = *lexer_list;
	if (*lexer_list == NULL)
	{
		*lexer_list = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}
