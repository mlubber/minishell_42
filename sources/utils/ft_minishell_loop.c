/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/05/28 14:03:27 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_print_list(t_lexer *ptr)
{
	t_lexer	*list_ptr;
	int		count;

	count = 1;
	list_ptr = ptr;
	if (list_ptr == NULL)
	{
		printf("No elements in list.\n");
		return ;
	}
	while (list_ptr != NULL)
	{
		printf("Node %d: [%s] %d\n", count, list_ptr->str, list_ptr->node_nbr);
		list_ptr = list_ptr->next;
		count++;
	}
}

int	ft_init_tools(t_tools *tools)
{
	tools->lexer_list = NULL;
	ft_parse_envp(tools);
	return (1);
}

int	ft_reset_tools(t_tools *tools)
{
	free(tools->args);
	ft_free_2d_arr(tools->paths);
	ft_init_tools(tools);
	ft_minishell_loop(tools);
	return (1);
}

int	ft_minishell_loop(t_tools *tools)
{
	char	*temp;

	tools->args = readline("minishell: ");
	temp = ft_strtrim(tools->args, " ");
	free(tools->args);
	tools->args = temp;
	if (tools->args[0] == '\0')
		return (ft_reset_tools(tools));
	else if (ft_strncmp(tools->args, "env", ft_strlen(tools->args)) == 0)
		ft_mini_env(tools);
	else if (ft_strncmp(tools->args, "pwd", ft_strlen(tools->args)) == 0)
		ft_mini_pwd(tools);
	else if (ft_strncmp(tools->args, "exit", ft_strlen(tools->args)) == 0)
		exit(EXIT_SUCCESS);
	else
	{
		printf("Full string: %s\n", tools->args);
	}
	ft_reader(tools);
	ft_print_list(tools->lexer_list);
	ft_reset_tools(tools);
	free(temp);
	return (1);
}
