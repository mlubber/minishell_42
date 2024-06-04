/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 07:07:14 by mlubbers      ########   odam.nl         */
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

// int	ft_init_tools(t_tools *tools)
// {
// 	tools->lexer_list = NULL;
// 	ft_parse_envp(tools);
// 	return (1);
// }

int	ft_reset_tools(t_tools *tools)
{
	free(tools->full_string);
	// ft_free_2d_arr(tools->paths);
	// ft_init_tools(tools);
	ft_minishell_loop(tools);
	return (1);
}

int	ft_minishell_loop(t_tools *tools)
{
	char	*string;

	tools->full_string = readline("minishell: ");
	string = ft_strtrim(tools->full_string, " "); // add fail check
	free(tools->full_string);
	tools->full_string = string;
	add_history(string);
	if (tools->full_string[0] == '\0')
		return (ft_reset_tools(tools));
	else if (ft_strncmp(tools->full_string, "env", ft_strlen(tools->full_string)) == 0)
		ft_mini_env(tools);
	else if (ft_strncmp(tools->full_string, "pwd", ft_strlen(tools->full_string)) == 0)
		ft_mini_pwd(tools);
	else if (ft_strncmp(tools->full_string, "export", ft_strlen(tools->full_string)) == 0)
		ft_mini_export(tools);
	else if (ft_strncmp(tools->full_string, "exit", ft_strlen(tools->full_string)) == 0)
	{
		free(string);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("Full string: %s\n", tools->full_string);
	}
	ft_reader(tools);
	ft_print_list(tools->lexer_list);
	ft_reset_tools(tools);
	free(string);
	return (1);
}
