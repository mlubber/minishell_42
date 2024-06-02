/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   kill_program.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: wsonepou <wsonepou@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/30 14:08:00 by wsonepou      #+#    #+#                 */
/*   Updated: 2024/06/02 12:33:46 by wsonepou      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	kill_program(t_tools *tools, char *msg, int i)
{
	if (tools->envp != NULL)
		ft_free_2d_arr(tools->envp);
	if (msg != NULL)
	{
		printf("%s\n", msg);
		exit(i);
	}
	exit(EXIT_SUCCESS);
}