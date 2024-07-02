/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_minishell_loop.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mlubbers <mlubbers@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/27 09:30:02 by mlubbers      #+#    #+#                 */
/*   Updated: 2024/07/02 13:47:05 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// This function gets called to check if a cmd is a builtin function
// *** split_input gets replaced by the command table linked list ***
int	builtin_check(t_shell *shell)
{
	int	x;

	x = 0;
	if (shell->input->cmds->cmds == NULL)
		return (0);
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
	t_file		*tmp_in;
	t_file		*tmp_out;
	
	int o = 0;
	int num = 0;
	tmp = shell->input->cmds;
	while (tmp != NULL)
	{
		tmp_in = tmp->infiles;
		tmp_out = tmp->outfiles;
		printf("\n--[NODE: %d]--\n", num);
		while (tmp_in != NULL)
		{
			printf("infile %d: %s ", o, tmp_in->str);
			if (tmp_in->type == t_in_file)
				printf("[< file]\n");
			else if (tmp_in->type == t_in_heredoc)
				printf("[<< heredoc]\n");
			tmp_in = tmp_in->next;
			o++;
		}
		o = 0;
		while (tmp_out != NULL)
		{
			printf("outfile %d: %s ", o, tmp_out->str);
			if (tmp_out->type == t_out_trunc)
				printf("[> trunc]\n");
			else if (tmp_out->type == t_out_append)
				printf("[>> append]\n");
			tmp_out = tmp_out->next;
			o++;
		}
		o = 0;
		while (tmp->cmds != NULL && tmp->cmds[o] != NULL)
		{
			if (tmp->cmds != NULL)
				printf("Cmd %d: %s\n", o, tmp->cmds[o]);
			o++;
		}
		o = 0;
		tmp = tmp->next;
		num++;
	}
	printf("\n");
}

void	start_execution(t_shell *shell)
{
		// if (builtin_check(shell) == 1)
		// 	continue ;
		// execute cmds here!
		free_cmd_list(&shell->input->cmds);	
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
		free (input);
		check_ctable(shell); // Testing all files and cmds
		start_execution(shell);
	}
	if (input != NULL)
		free (input);
}
