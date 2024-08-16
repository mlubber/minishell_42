/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mini_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/07 11:27:19 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/08/16 16:41:07 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"




// void	check_mini_exit_arg(t_shell *shell, char **cmds)
// {
// 	int		i;
// 	bool	num;

// 	num = true;
// 	i += check_whitespace(cmds[1], 0);
// 	if (cmds[1][i] == '-' && cmds[1][i + 1] == '-' && cmds[1][i + 2] == '\0')
// 		kill_program(shell, "exit", 0);
// 	while (cmds[1][i])
// 	{
// 		if (ft_isdigit(cmds[1][i]) == 0)
// 		{
// 			num = false;
// 			break ;
// 		}
// 		i++;
// 	}
// }

int	ft_mini_exit(t_shell *shell, char **cmds)
{
	if (cmds[1] != NULL)
	{
		// check_mini_exit_arg(shell, cmds);
		// printf("Exit does not take arguments!\n");
		return (1);
	}
	// if (shell->input->cnode->next)
	// 	kill_program(shell, NULL, 0);
	// else
		kill_program(shell, "exit", 0);
	return (1);
}
