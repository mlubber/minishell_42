/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/06/13 17:38:47 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This function gets called to check if a cmd is a builtin function
// *** split_input gets replaced by the command table linked list ***
int	builtin_check(t_shell *shell)
{
	int	x;

	x = 0;
	if (ft_strncmp(shell->input->cmds->cmds[0], "echo", 5) == 0)
		x = ft_mini_echo(shell, shell->input->cmds->cmds);
	else if (ft_strncmp(shell->input->cmds->cmds[0], "cd", 3) == 0)
		x = ft_mini_cd(shell, shell->input->cmds->cmds);
	else if (ft_strncmp(shell->input->cmds->cmds[0], "pwd", 4) == 0)
		x = ft_mini_pwd(shell, shell->input->cmds->cmds);
	else if (ft_strncmp(shell->input->cmds->cmds[0], "export", 7) == 0)
		x = ft_mini_export(shell, shell->input->cmds->cmds);
	else if (ft_strncmp(shell->input->cmds->cmds[0], "unset", 6) == 0)
		x = ft_mini_unset(shell, shell->input->cmds->cmds);
	else if (ft_strncmp(shell->input->cmds->cmds[0], "env", 4) == 0)
		x = ft_mini_env(shell, shell->input->cmds->cmds);
	else if (ft_strncmp(shell->input->cmds->cmds[0], "exit", 5) == 0)
		x = ft_mini_exit(shell, shell->input->cmds->cmds);
	if (x == 1)
		return (1);
	return (0);
}

void	check_ctable(t_shell *shell) // TESTING PURPOSES
{
	t_ctable	*tmp;
	
	int o = 0;
	int num = 0;
	tmp = shell->input->cmds;
	while (tmp != NULL)
	{
		printf("\n--[NODE: %d]--\n", num);
		if (tmp->type == 0)
			printf("Type: cmd\n");
		else if (tmp->type == 1)
			printf("Type: |\n");
		else if (tmp->type == 2)
			printf("Type: <\n");
		else if (tmp->type == 3)
			printf("Type: <<\n");
		else if (tmp->type == 4)
			printf("Type: >\n");
		else if (tmp->type == 5)
			printf("Type: >>\n");
		while (tmp->cmds != NULL && tmp->cmds[o] != NULL)
		{
			if (tmp->cmds != NULL)
				printf("Cmd %d: %s\n", o, tmp->cmds[o]);
			o++;
		}
		if (tmp->file != NULL)
			printf("file %d: %s\n", o, tmp->file);
		o = 0;
		tmp = tmp->next;
		num++;
	}
}

// The minishell loop that keeps minishell running. We check if input is correct,
// then add the input to readline history, then split the input into a 2d array
// *** split_input gets replaced by the command table linked list ***
void	ft_minishell_loop(t_shell *shell)
{
	char	*input;

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
		create_ctable(shell, input);
		check_ctable(shell);
		free (input);
		if (builtin_check(shell) == 1)
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
