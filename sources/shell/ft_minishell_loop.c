/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/04 16:36:01 by mlubbers      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_print_list(t_lexer *ptr)
// {
// 	t_lexer	*list_ptr;
// 	int		count;

// 	count = 1;
// 	list_ptr = ptr;
// 	if (list_ptr == NULL)
// 	{
// 		printf("No elements in list.\n");
// 		return ;
// 	}
// 	while (list_ptr != NULL)
// 	{
// 		printf("Node %d: [%s] %d\n", count, list_ptr->str, list_ptr->node_nbr);
// 		list_ptr = list_ptr->next;
// 		count++;
// 	}
// }

void	ft_minishell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell: ");
		if (input == NULL || ft_strncmp(input, "exit", 5) == 0)
			break ;
		else if (input[0] == '\0')
		{
			free (input);
			continue ;
		}
		if (input[0] != ' ')
			add_history(input);
		shell->input = ft_strtrim(input, " ");
		free (input);
		if (shell->input == NULL)
			kill_program(shell, "Failed mallocing strtrim command!", 6);
		else if (ft_strncmp(shell->input, "env", ft_strlen(shell->input)) == 0)
			ft_mini_env(shell);
		else if (ft_strncmp(shell->input, "pwd", ft_strlen(shell->input)) == 0)
			ft_mini_pwd(shell);
		else if (ft_strncmp(shell->input, "export", ft_strlen(shell->input)) == 0)
			ft_mini_export(shell);
		else if (ft_strncmp(shell->input, "cd", ft_strlen(shell->input)) == 0)
			ft_mini_cd(shell);
		else
		{
			printf("Full string: %s\n", shell->input);
		}
	}
	if (input != NULL)
		free (input);
	// ft_reader(shell);
}


// int	ft_reset_shell(t_shell *shell)
// {
// 	free(shell->input);
// 	// ft_free_2d_arr(shell->paths);
// 	// ft_init_shell(shell);
// 	ft_minishell_loop(shell);
// 	return (1);
// }

// int	ft_minishell_loop(t_shell *shell)
// {
// 	char	*string;

// 	shell->input = readline("minishell: ");
// 	string = ft_strtrim(shell->input, " "); // add fail check
// 	free(shell->input);
// 	shell->input = string;
// 	add_history(string);
// 	if (shell->input[0] == '\0')
// 		return (ft_reset_shell(shell));
// 	else if (ft_strncmp(shell->input, "env", ft_strlen(shell->input)) == 0)
// 		ft_mini_env(shell);
// 	else if (ft_strncmp(shell->input, "pwd", ft_strlen(shell->input)) == 0)
// 		ft_mini_pwd(shell);
// 	else if (ft_strncmp(shell->input, "export", ft_strlen(shell->input)) == 0)
// 		ft_mini_export(shell);
// 	else if (ft_strncmp(shell->input, "cd", ft_strlen(shell->input)) == 0)
// 		ft_mini_cd(shell);
// 	else if (ft_strncmp(shell->input, "exit", ft_strlen(shell->input)) == 0)
// 	{
// 		free(string);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		printf("Full string: %s\n", shell->input);
// 	}
// 	ft_reader(shell);
// 	// ft_print_list(shell->lexer_list);
// 	ft_reset_shell(shell);
// 	free(string);
// 	return (1);
// }

// void    minishell_loop(void)
// {
//     char    *line;    line = NULL;
//     while (1)
//     {
//         line = readline("Minishell> ");
//         if (line == NULL || ft_strncmp(line, "exit", 5) == 0)
//             //(ctrl+D) makes sure it doesnt acces adress 0 (invalid) and segfault later
//         {
//             rl_clear_history(); // clears the saved history
//             printf("exit\n");
//             break ;
//                 // it should exit our program like bash with our buildin exit
//         }
//         printf("--%s--\n", line); // Check if input is stored.
//         if (*line)
//             add_history(line);
//         free(line);
//     }
//     return;
// }