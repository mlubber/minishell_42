/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/07 18:38:11 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int	builtin_check(t_shell *shell, char **split_input)
{
	int	x;

	x = 0;
	if (ft_strncmp(split_input[0], "echo", 5) == 0)
		x = ft_mini_echo(shell, split_input);
	else if (ft_strncmp(split_input[0], "cd", 3) == 0)
		x = ft_mini_cd(shell, split_input);
	else if (ft_strncmp(split_input[0], "pwd", 4) == 0)
		x = ft_mini_pwd(shell, split_input);
	else if (ft_strncmp(split_input[0], "export", 7) == 0)
		x = ft_mini_export(shell, split_input);
	else if (ft_strncmp(split_input[0], "unset", 6) == 0)
		x = ft_mini_unset(shell, split_input);
	else if (ft_strncmp(split_input[0], "env", 4) == 0)
		x = ft_mini_env(shell, split_input);
	else if (ft_strncmp(split_input[0], "exit", 5) == 0)
		x = ft_mini_exit(shell, split_input);
	if (x == 1)
		return (1);
	return (0);
}

void	ft_minishell_loop(t_shell *shell)
{
	char	*input;
	char	**split_input;

	while (1)
	{
		input = readline("minishell: ");
		if (input == NULL)
			break ;
		else if (input[0] == '\0')
		{
			free (input);
			continue ;
		}
		add_history(input);
		if (input_checker(&input) == 1)
			continue ;
		split_input = input_splitter(input);
		free (input);
		if (split_input == NULL)
			kill_program(shell, "Failed parsing input!", 6);
		if (builtin_check(shell, split_input) == 1)
			continue ;
	}
	if (input != NULL)
		free (input);
}

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
