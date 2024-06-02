/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lexer_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/28 11:40:42 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/28 13:55:38 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_lexer	*ft_new_lexer_node(char *str)
{
	t_lexer		*new_node;
	static int	i = 0;

	new_node = (t_lexer *)malloc(sizeof(t_lexer));
	if (new_node == NULL)
		return (0);
	new_node->str = str;
	new_node->node_nbr = i++;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lexer_add_back(t_lexer **lexer_list, t_lexer *new)
{
	t_lexer	*temp;

	// if (!lexer_list)
	// {
	// 	printf("Error: lexer_list is NULL\n");
	// 	return ;
	// }
	// if (!new)
	// {
	// 	printf("Error: new node is NULL\n");
	// 	return ;
	// }
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
